//server

#include "sharedFunction.h"


char* transformacoesNome[]={
    "nop",
    "bcompress",
    "bdecompress",
    "gcompress",
    "gdecompress",
    "encrypt",
    "decrypt",
    NULL
};

char* transformations_folder;

int config[TRANS_NR];//nr maximos de cada tipo de filtros que podem executar ao mesmo tempo
int using[TRANS_NR];//nr de filtros de cada tipo que estao a executar no momento presente

int pendingRequestsIdx[100][2];//pedidos em espera             idTask | fifoU
int nrpendingRequests;//numero de pedidos em espera

int runningRequestsIdx[100];//pedidos a correr
int nrrunningRequests;//numero de pedidos a correr

int waiting[100][2];// pid | idxTask
int nrwaitingProcess;

Pedido tasks[MAX_STORE];//todos os pedidos enviados para o servidor
int tasksNr;

pid_t pidServidor;
int backbone;
int alrm;

int accStarvation;

int readConfigFile(char *path){
    int fd;
    if((fd = open(path,O_RDONLY)) == ERROR){
        perror("error opening config file");
        return ERROR;
    }
    else{
        char* line = malloc(1024);
        int bytes_read;

        if((bytes_read=read(fd,line,1024))==ERROR){
            perror("reading config file");
            if (line) free(line);
            return ERROR; 
        }
        char* string = malloc(1024);
        int nr, i, lineNr=0;
        if(bytes_read>=1024)
            perror("config file too big, some filters could not loaded");

        for (i = 0; i < bytes_read; i++){
            if(line[i]=='\n')
                lineNr++;
        }
        for(i=0;i<lineNr;i++){ 
            strcpy(string, strsep(&line, "\n"));
            char*temp=malloc(1024);
            int n = sscanf(string, "%s %d" , temp, &nr);
            if(n != 2){
                perror("erro de sintaxe no ficheiro config");
                if (line)
                    free(line);
                if (string)
                    free(string);
                continue;
            }
            
            for (int i = 0; i < TRANS_NR; i++){
                if (!strcmp(temp, transformacoesNome[i])){
                    config[i]=nr;
                    break;
                }
            }
            if(temp)
                free(temp);
        }
        close(fd);
        if (string)
            free(string);
    }
    return OK;
}

int aplicarTransformacoes(Pedido req){//assumindo que o redirecionamento já está feito antes...
    int i, p[2];

    for (i=4; i < req->elems-1; i++){
        int res = pipe(p);
        if(res==ERROR){
            perror("error creating pipe");
            return ERROR;
        }
        pid_t pid;

        char* tmp = strdup(req->args[i]);
        if((pid = fork())==0){
            dup2(p[1],1);
            if(close(p[1])==ERROR){
                perror("closing fd (aplicar transformacoes)");
                _exit(ERROR);
            }
            if( close(p[0])==ERROR){
                perror("closing fd (aplicar transformacoes)");
                _exit(ERROR);
            }
            
            if(execl(concatStrings(concatStrings(transformations_folder, "/"),tmp),tmp,NULL) == ERROR){
                perror("Erro a aplicar filtro");
                _exit(ERROR);
            }
        }
        else{
            dup2(p[0],0);
            if(close(p[0])==ERROR){
                perror("closing fd (aplicar transformacoes)");
            }
            if(close(p[1])){
                perror("closing fd (aplicar transformacoes)");
            } 
            free(tmp);
        }
    }
    char* tmp = strdup(req->args[i]);
    if(execl(concatStrings(concatStrings(transformations_folder, "/"),tmp),tmp,NULL) == ERROR){
        perror("Erro a aplicar filtro");
        free(tmp);
        return(ERROR);
    }
    free(tmp);
    return OK;
}



//-------------------- ADICIONAR/REMOVER DE FILAS --------------------
int addPending(int idxTask, int fifoU, int priori){//adiciona no sitio correto da fila o idxTask e o fifoU da tarefa que fica pendente
    int i;
    for (i = 0; i < nrpendingRequests; i++){
        if(priori<tasks[pendingRequestsIdx[i][0]]->priority)
            break;
    }
    for (int j = nrpendingRequests; j > i; j--){
        pendingRequestsIdx[j][0] = pendingRequestsIdx[j-1][0];
        pendingRequestsIdx[j][1] = pendingRequestsIdx[j-1][1];
    }
    pendingRequestsIdx[i][0] = idxTask;
    pendingRequestsIdx[i][1] = fifoU;
    nrpendingRequests++;
    return i;
}

void addRunning(int id){//adiciona ao fim da fila o idxTask que passa vai ficar a correr e atualiza array using
    for (int i = 4; i < tasks[id]->elems; i++){
        char* filtro = tasks[id]->args[i];
        for (int i = 0; i < TRANS_NR; i++){
            if (!strcmp(filtro, transformacoesNome[i])){
                using[i]+=1;
                break;
            }
        }
    }
    runningRequestsIdx[nrrunningRequests] = id;
    nrrunningRequests++;
}

int addTask(Pedido temp){//adiciona a struct ao fim da fila 
    tasks[tasksNr] = temp;
    tasksNr++;
    return tasksNr-1;
}

void addWaiting(int pid, int idx){
    waiting[nrwaitingProcess][0] = pid;
    waiting[nrwaitingProcess][1] = idx;
    nrwaitingProcess++;
}

void removeWaiting(int pid){
    int i;
    for (i = 0; i < nrwaitingProcess; i++){
        if(waiting[i][0]==pid)
            break;
    }
    if(i==nrwaitingProcess){
        perror("invalid pid\n");
        return;
    }
    nrwaitingProcess--;
    for (int j = i; j < nrwaitingProcess; i++){
        waiting[j][0] = waiting[j+1][0];
        waiting[j][1] = waiting[j+1][1];
    }
    waiting[nrwaitingProcess][0] = -1;
    waiting[nrwaitingProcess][1] = -1;
}

int removePending(int index){
    nrpendingRequests--;
    int result=pendingRequestsIdx[index][1];
    for (int i = index; i < nrpendingRequests; i++){
        pendingRequestsIdx[i][0] = pendingRequestsIdx[i+1][0];
        pendingRequestsIdx[i][1] = pendingRequestsIdx[i+1][1];
    }
    pendingRequestsIdx[nrpendingRequests][0]=-1;
    pendingRequestsIdx[nrpendingRequests][1]=-1;
    return result;//devolve fifo onde deve comunicar 
}

void removeRunning(int index){
    for (int j = 4; j < tasks[index]->elems; j++){
        char* filtro = tasks[index]->args[j];
        for (int i = 0; i < TRANS_NR; i++){
            if (!strcmp(filtro, transformacoesNome[i])){
                using[i]-=1;
                break;
            }
        }
    }
    int in;
    for (in = 0; in < nrrunningRequests; in++){
        if(runningRequestsIdx[in]==index)
            break;
    }
    
    nrrunningRequests--;
    for (int i = in; i < nrrunningRequests; i++){
        runningRequestsIdx[i] = runningRequestsIdx[i+1];
    }
    runningRequestsIdx[nrrunningRequests]=-1;
}
//------------------------------------------------------------


//-------------------- INFORMATION SENDERS --------------------
void showSatus(int fifo){
    char* buf = malloc(1024);
    strcpy(buf, "---RUNING REQUESTS---\n");
    write(fifo, buf, strlen(buf));
    for(int i=0;i<nrrunningRequests;i++){
        int idx = runningRequestsIdx[i];
        char* full = "";//verificar
        for (int i = 0; i < tasks[idx]->elems; i++){
            char* tmp = concatStrings(tasks[idx]->args[i], " ");
            full = concatStrings(full, tmp);
            if(tmp)
                free(tmp);
            if(i==1){
                char* pri=malloc(77);
                sprintf(pri, "%d ", tasks[idx]->priority);//rever isto !!!!!!!!!!!
                full = concatStrings(full, pri);
                if(pri)
                    free(pri);
            }
        }
        sprintf(buf,"task #%d: (pid)%s\n", idx, full);//imprime as que estao a correr no momento
        if(full)
            free(full);

        write(fifo, buf, strlen(buf));
    }

    strcpy(buf, "\n---PENDING REQUESTS---\n");
    write(fifo, buf, strlen(buf));

    for(int i=0;i<nrpendingRequests;i++){
        int idx = pendingRequestsIdx[i][0];
        char *full= malloc(1024);
        strcpy(full, "");
        for (int i = 0; i < tasks[idx]->elems; i++){
            char* tmp = concatStrings(tasks[idx]->args[i], " ");
            full = concatStrings(full, tmp);
            if(tmp)
                free(tmp);
            if(i==1){
                char* pri=malloc(77);
                sprintf(pri, "%d ", tasks[idx]->priority);//rever isto !!!!!!!!!!!
                full = concatStrings(full, pri);
                if(pri)
                    free(pri);
            }
        }

        sprintf(buf,"pending #%d: (pid)%s\n", idx, full);//imprime as que estao a correr no momento
        if(full)
            free(full);

        write(fifo, buf, strlen(buf));
    }

    strcpy(buf, "\n---SERVER CONFIGURATIONS---\n");
    write(fifo, buf, strlen(buf));
    for(int i=0;i<TRANS_NR;i++){
        sprintf(buf,"transf %s: %d/%d (running/max)\n", transformacoesNome[i], using[i], config[i]);//estado de ocupacao de cada uma das transformacoes
        write(fifo, buf, strlen(buf));
    }
    if(buf)
        free(buf);
}

void showPendent(int fifo){
    write(fifo, SERVICE_PENDENT, strlen(SERVICE_PENDENT));
}

void showRunning(int fifo){
    write(fifo, SERVICE_RUNNING, strlen(SERVICE_RUNNING));
}

void showConclued(int fifo, off_t sizeBegin, off_t sizeEnd){
    write(fifo, SERVICE_FINISHED, strlen(SERVICE_FINISHED));
    char *tmp = malloc(1024);
    sprintf(tmp, "(bytes-input: %ld, bytes-output: %ld)\n", sizeBegin, sizeEnd);
    write(fifo, tmp, strlen(tmp));
    if(tmp)
        free(tmp);
}
//------------------------------------------------------------



int goPendingOrNot(Pedido req){
    int after[TRANS_NR];
    for (int i = 0; i < TRANS_NR; i++){
        after[i] = using[i];
    }
    for (int i = 4; i < req->elems; i++){
        char* tmp =strdup(req->args[i]);
        for(int j=0;j<TRANS_NR;j++){
            if(!strcmp(tmp, transformacoesNome[j])){
                after[j]++;
                break;
            }
        }
        free(tmp);
    }
    for (int i = 0; i < TRANS_NR; i++){
        if(after[i]>config[i]){
            return ERROR;
        }
    }
    return OK;
}

void increasePriorities(){//evitar Starvation, a cada 11 SIGSUR1 aumenta as prioridades de todos abaixo de 5
    for (int i = 0; i < nrpendingRequests; i++){
        if(tasks[pendingRequestsIdx[i][0]]->priority == 5)
            break;
        tasks[pendingRequestsIdx[i][0]]->priority += 1;
    }
}



//-------------------- HANDLERS --------------------
void handlerGracioso(int num){
    char* tmp = "[GRACIOSA]\n";
    write(1, tmp, strlen(tmp));

    kill(alrm, SIGKILL);
    close(backbone);

    while (nrpendingRequests>0){
        int fifoU = pendingRequestsIdx[0][1];
        write(fifoU, SERVICE_ABORTED, strlen(SERVICE_ABORTED));
        close(fifoU);
        removePending(0);
    }
    
    while (nrrunningRequests>0 || nrwaitingProcess>0){
        int status;
        for (int i = 0; i < nrwaitingProcess; i++){
            int pid = waiting[i][0];
            if(waitpid(pid, &status, WNOHANG)!=0){
                int idxTask = waiting[i][1];
                removeWaiting(pid);
                removeRunning(idxTask);
                i--;
            }
        }
    }
}

void handlerDependences(int num){
    accStarvation++;
    if(accStarvation==STARVATION_COUNT){
        increasePriorities();
        accStarvation=0;
    }

    char* tmp1 = "[DEPENDENCIAS]\n";
    write(1, tmp1, strlen(tmp1));
    
    //lidar Waitting
    int status;
    for (int i = 0; i < nrwaitingProcess; i++){
        int pid = waiting[i][0];
        if(waitpid(pid, &status, WNOHANG)!=0){
            int idxTask = waiting[i][1];
            removeWaiting(pid);
            removeRunning(idxTask);
            i--;
        }
    }
    
    //lidar Pendentes
    for (int i = nrpendingRequests-1; i >= 0; i--){
        int idxTask = pendingRequestsIdx[i][0];
        if(goPendingOrNot(tasks[idxTask])==OK){
            int fifoU = removePending(i);
            // ATENCAO VER SE NAO MUDA NADA, RECOPIAR O CODIGO DA MAIN DE NOVO MAIS PARA A FRENTE daqui para baixo só !!! e resolver possiveis problemas com variaveis usadas

            addRunning(idxTask);
            int pid1, pid2;
                
            if((pid1=fork())==0){// para não deixar o processo que corre o servidor à espera fazer double fork 
                int status2;
                if ((pid2=fork())==0){
                    showRunning(fifoU);

                    redirecionar(tasks[idxTask]->args[2], tasks[idxTask]->args[3]);
                    aplicarTransformacoes(tasks[idxTask]);
                    _exit(OK);
                }
                else{
                    waitpid(pid2, &status2, 0);
                    char *tmp2 = "pai: pedido acabado!!!\n";
                    write(1, tmp2, strlen(tmp2));
                    off_t sizeBegin = calculaTamanho(tasks[idxTask]->args[2]);
                    off_t sizeEnd = calculaTamanho(tasks[idxTask]->args[3]);
                    showConclued(fifoU, sizeBegin, sizeEnd);

                    kill(pidServidor, SIGUSR1);//manda o servidor ver pendentes e waitings

                }
                _exit(OK);
            }
            //daqui para a frente está no processo principal
            else{
                int stat;
                if(waitpid(pid1, &stat, WNOHANG)==0){
                    addWaiting(pid1, idxTask);
                }
                else{
                    removeRunning(idxTask);
                }
            }
            close(fifoU);//como o filho do filho tem copia do descritor pode usa-la
        }
    }
}

void handlerAlarm(int num){
    //char* tmp = "[ALARM]\n";
    //write(1, tmp, strlen(tmp));
    alarm(ALARM_TIME);
}
//------------------------------------------------------------


int main(int argc, char const *argv[]){
    setbuf(stdout, NULL);

    // -------------- validating arguments and configuring server settings -------------- 
    if(argc!=3){
        perror("invalid arguments to run the server");
        return ERROR;
    }

    if(signal(SIGALRM, handlerAlarm) == SIG_ERR){
        perror("sigAlarm error");
        return ERROR;
    }
    if(signal(SIGTERM, handlerGracioso) == SIG_ERR){
        perror("sigTerm error");
        return ERROR;
    }
    if(signal(SIGUSR1, handlerDependences) == SIG_ERR){
        perror("sigTerm error");
        return ERROR;
    }
    int res;
    if((res = readConfigFile((char*)argv[1])) == ERROR){
        return ERROR;
    }
    transformations_folder = strdup((char*)argv[2]);
    

    // -------------- inicializations -------------- 
    nrpendingRequests=0;
    nrrunningRequests=0;
    tasksNr=0;
    nrwaitingProcess=0;
    accStarvation = 0;
    for (int i = 0; i < 7; i++){
        using[i]=0;
    }
    for (int i = 0; i < 100; i++){
        pendingRequestsIdx[i][0] = -1;
        pendingRequestsIdx[i][1] = -1;
        runningRequestsIdx[i] = -1;
        waiting[i][0] = -1;
        waiting[i][1] = -1;
    }
    for (int i = 0; i < MAX_STORE; i++){
        tasks[i]=NULL;
    }
    
    
    // -------------- handle fifos -------------- 
    int fifoW, fifoU, n;
    if((res = mkfifo(WRITE_NAME, 0622)) == ERROR){// rw-w--w--
        perror("error creating the fifo Write(client)");
        if(transformations_folder)
            free(transformations_folder);
        return ERROR;
    }

    pidServidor = getpid();
    char* tmp = malloc(1024);
    sprintf(tmp, "[Debug]Ready to accept client requests. Mypid<%d>\n", pidServidor);
    write(1, tmp, strlen(tmp));
    if ((fifoW = open(WRITE_NAME, O_RDONLY, 0622)) == ERROR){
        perror("Erro a abrir FIFO(write)");
        if(transformations_folder)
            free(transformations_folder);
        return ERROR;
    }
    // na graciosa fechar este e acaba o while
    if ((backbone = open(WRITE_NAME, O_WRONLY)) == ERROR){//backbone, nunca vai receber EOF na leitura
        perror("Erro a abrir FIFO(write)");
        if(transformations_folder)
            free(transformations_folder);
        return ERROR;
    }
    // ------------------------------------------ 
    


    // -------------- alarm subroutine -------------- 
    if((alrm=fork())==0){//criar subrotina de alarme para dizer ao servidor para constantemente verificar por coisas pendentes/waitings
        alarm(ALARM_TIME);
        while (1){
            pause();//espera que o alarme acabe
            kill(pidServidor, SIGUSR1);//manda o servidor ver pendentes e waitings
        }
        _exit(OK);//nunca chega a isto??
    }
    // ------------------------------------------ 


    Pedido temporary = malloc(sizeof(struct pedido));
    while((n = read(fifoW,temporary,sizeof(struct pedido))) > 0){//ler do cliente
        Pedido infoStruct = malloc(sizeof(struct pedido));
        copyStruct(temporary, infoStruct);

        //------Abertura de um fifo unico para o Cliente--------
        char* newFifoName = malloc(1024);
        sprintf(newFifoName, "%s%s",READ_NAME, infoStruct->args[0]);//fifo especifico para enviar mensagens para processo especifico

        if ((fifoU = open(newFifoName,O_WRONLY, 0644)) == ERROR){
            perror("Erro a abrir FIFO(read)");
            if(newFifoName)
                free(newFifoName);
            if(infoStruct)
                free(infoStruct);
            continue;
        }
        //----------------------------

        if(infoStruct->elems==2){//recebe pedido de status
            kill(pidServidor, SIGUSR1);//manda o servidor ver pendentes e waitings
            
            showSatus(fifoU);
            close(fifoU);
            free(newFifoName);
        }else{
            int position = addTask(infoStruct);
            if( goPendingOrNot(infoStruct) == ERROR ){
                addPending(position, fifoU, infoStruct->priority);//esperar ate que o sinal SIGSUR1 faca a sua parte 
                showPendent(fifoU);
            }else{
                addRunning(position);
                int pid1, pid2;
                
                if((pid1=fork())==0){// para não deixar o processo que corre o servidor à espera fazer double fork 
                    int status2;
                    if ((pid2=fork())==0){
                        showRunning(fifoU);
                        
                        redirecionar(infoStruct->args[2], infoStruct->args[3]);
                        aplicarTransformacoes(infoStruct);
                        _exit(OK);
                    }
                    else{
                        waitpid(pid2, &status2, 0);
                        char *tmp2 = "pai: pedido acabado!!!\n";
                        write(1, tmp2, strlen(tmp2));
                        off_t sizeBegin = calculaTamanho(infoStruct->args[2]);
                        off_t sizeEnd = calculaTamanho(infoStruct->args[3]);
                        showConclued(fifoU, sizeBegin, sizeEnd);

                        kill(pidServidor, SIGUSR1);//manda o servidor ver pendentes e waitings
                        _exit(OK);
                    }
                }
                //daqui para a frente está no processo principal
                else{
                    int stat;
                    if(waitpid(pid1, &stat, WNOHANG)==0){
                        addWaiting(pid1, position);
                    }
                    else{
                        removeRunning(position);
                    }
                }
                close(fifoU);//como o filho do filho tem copia do descritor pode usa-la
                kill(pidServidor, SIGUSR1);
            }
            if(newFifoName)
                free(newFifoName);
        }
    }
    if(n==ERROR){
        perror("error reading from fifoW");
    }
    close(fifoW);
    unlink(WRITE_NAME);//unlink nao apaga, logo. só quando todos fecham o fd.
    
    
    if(temporary)
        free(temporary);
    for (int i = 0; i < tasksNr; i++){
        if(tasks[i])
            free(tasks[i]);
    }
    
    if(transformations_folder)
        free(transformations_folder);

    return 0;
}
