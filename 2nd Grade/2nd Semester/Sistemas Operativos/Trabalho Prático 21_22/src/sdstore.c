//client

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

int verificarSintax(const char** transformacoes, int nTransf){//antes de enviar para server passar por isto
    int count=0;
    for (int i = 0; i < nTransf; i++){
        for (int j = 0; j < TRANS_NR; j++){
            if (!strcmp(transformacoes[i], transformacoesNome[j])){
                count++;
                break;
            }
        }
    }
    return count;
}

int main(int argc, char const *argv[]){

    setbuf(stdout, NULL);
    int fd, n, res;
    int pid=getpid();
    
    if(argc==1){// ./sdstore
        char* info = "./sdstore status\n./sdstore proc-file priority input-filename output-filename transformation-id-1 transformation-id-2 ...\n";
        write(STDOUT_FILENO, info, strlen(info));
    }
    else if((argc==2 && !strcmp(argv[1],"status")) || (argc>=6 && !strcmp(argv[1], "proc-file") && atoi(argv[2])>=0 && atoi(argv[2])<=5)){
        char* newFifoName = malloc(1024);
        sprintf(newFifoName, "%s%d", READ_NAME, pid);//fifo especifico para receber mensagens só neste precesso
        if((res = mkfifo(newFifoName, 0644)) == ERROR){// rw-r--r--
            perror("error creating the fifo Read(client)");
            free(newFifoName);
            return ERROR;
        }

        if ((fd=open(WRITE_NAME, O_WRONLY))==ERROR){
            perror("error opening fifoWrite");
            unlink(newFifoName);
            free(newFifoName);
            return ERROR;
        }
        Pedido req = malloc(sizeof(struct pedido));

        sprintf(req->args[1], "%s", argv[1]);

        if(argc==2){
            req->elems = argc;
            req->priority = -1;
        }
        else{
            req->elems = argc-1;
            req->priority = atoi(argv[2]);

            for (int i = 3; i < argc; i++){
                sprintf(req->args[i-1], "%s", argv[i]);
            }
        }
        sprintf(req->args[0], "%d", pid);
     
        char *debug1 = malloc(77);
        sprintf(debug1, "[Debug]PID->%d<-\n", pid);
        write(1, debug1, strlen(debug1));
        free(debug1);

        write(fd, req, sizeof(struct pedido));
        close(fd);//ver se deixa de dar por causa disto

        if ((fd=open(newFifoName, O_RDONLY))==ERROR){
            perror("error opening fifoRead(unico)");
            unlink(newFifoName);
            free(newFifoName);
            free(req);
            return ERROR;
        }
        char* buffer = malloc(1024);
        while((n = read(fd,buffer,1024)) > 0){
            write(STDOUT_FILENO,buffer,n);
        }

        close(fd);
        
        unlink(newFifoName);
        free(newFifoName);
        free(req);
        free(buffer);
        
        if(n==ERROR){
            perror("error reading from fifo");
            return ERROR;
        }
    }
    else{
        perror("error on the input arguments");
        return ERROR;
    }

    return OK;
}
