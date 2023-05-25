#include "files.h"

/* Experimente de seguida provocar um atraso antes do pai enviar o inteiro (p. ex., sleep(5)). Note
agora que a leitura do filho bloqueia enquanto o pai não realizar a operação de escrita no pipe. */

int main(int argc,const char* argv[]){
    int pipe_fd[2];
    pid_t pid;
    int num;
    int status;

    if (pipe(pipe_fd) == -1) return -1;
    if((pid = fork()) == 0){
        close(pipe_fd[1]);
        read(pipe_fd[0],&num,sizeof(int));
        close(pipe_fd[0]);
        printf("O processo filho recebeu do pai: %d\n",num);
        _exit(0);

    } else{
        close(pipe_fd[0]);
        sleep(5);
        num = 42;
        write(pipe_fd[1],&num,sizeof(int));
        close(pipe_fd[1]);
        wait(&status);
    }

    return 0;
}