#include "files.h"

/* Experimente de seguida provocar um atraso antes do pai ler o inteiro. Repita com uma sequência de
inteiros. Note agora que escrita do filho bloqueia enquanto o pai não realizar a operação de leitura no
pipe. */

int main(int argc,const char* argv[]){
    int pipe_fd[2];
    int num;

    if(pipe(pipe_fd) == -1) return -1;
    pid_t pid;
    if((pid = fork()) == 0){
        close(pipe_fd[0]);
        for(num = 33;num < 40;num++){
            write(pipe_fd[1],&num,sizeof(int));
        } 
        
        close(pipe_fd[1]);
        _exit(0);

    } else{
        close(pipe_fd[1]);
        for(int i = 0;i < 7;i++){
            //sleep(3);
            read(pipe_fd[0],&num,sizeof(int));
            printf("O processo pai recebeu do filho: %d\n",num);
        }
        close(pipe_fd[0]);
    }

    return 0;
}