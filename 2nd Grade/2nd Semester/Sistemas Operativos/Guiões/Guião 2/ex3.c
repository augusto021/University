#include "files.h"

/* Implemente um programa que crie dez processos filhos que deverão executar sequencialmente. Para este
efeito, os filhos podem imprimir o seu PID e o do seu pai, e finalmente, terminarem a sua execução com
um valor de saída igual ao seu número de ordem (e.g.: primeiro filho criado termina com o valor 1). O
pai deverá imprimir o código de saída de cada um dos seus filhos. */

int main(int argc,const char* argv[]){
    for(int i = 1;i < 11;i++){
        if(fork() == 0){
            printf("PID Filho: %d\n", getpid());
            printf("PID Pai: %d\n", getppid());
            _exit(i);

        } else{
            int status;
            wait(&status);
            printf("Exit: %d\n",WEXITSTATUS(status));
        }
    }

    return 0;
}