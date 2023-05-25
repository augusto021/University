#include "files.h"

/* Escreva um programa que crie um pipe anónimo e de seguida crie um processo filho. Experimente o pai
enviar um inteiro através do descritor de escrita do pipe, e o filho receber um inteiro a partir do respetivo
descritor de leitura. */

int main(int argc,const char* argv[]){
    int pipe_fd[2];
    int num;

    if (pipe(pipe_fd) == -1) return -1;
    pid_t pid;
    if((pid = fork()) == 0){
        close(pipe_fd[1]);
        read(pipe_fd[0],&num,sizeof(int));
        close(pipe_fd[0]);
        printf("O processo filho recebeu do pai: %d\n",num);
        _exit(0);

    } else{
        close(pipe_fd[0]);
        int num = 21;
        write(pipe_fd[1],&num,sizeof(int));
        close(pipe_fd[1]);
    }

    return 0;
}