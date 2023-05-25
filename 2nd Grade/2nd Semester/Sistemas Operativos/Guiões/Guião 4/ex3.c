#include "files.h"

/* Experimente agora inverter os papéis de modo à informação ser transmitida do filho para o pai. */

int main(int argc,const char* argv[]){
    int pipe_fd[2];
    int num;

    if (pipe(pipe_fd) == -1) return -1;
    pid_t pid;

    if((pid = fork()) == 0){
        close(pipe_fd[0]);
        num = 21;
        write(pipe_fd[1],&num,sizeof(int));
        close(pipe_fd[1]);
        _exit(0);

    } else{
        close(pipe_fd[1]);
        read(pipe_fd[0],&num,sizeof(int));
        close(pipe_fd[0]);
        printf("O processo pai recebeu do filho: %d\n",num);
    }

    return 0;
}