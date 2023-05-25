#include "files.h"

/* Implemente um programa que crie dez processos filhos que deverão executar em concorrência. O pai
deverá esperar pelo fim da execução de todos os seus filhos, imprimindo os respetivos códigos de saída. */


int main(int argc,const char* argv[]){
    int status;

    for(int i = 1;i < 11;i++){
        if(fork() == 0){
            sleep(3);
            printf("Filho %d terminou.\n",i);
            _exit(i);
        }
    }

    for(int i = 1;i < 11;i++){
        waitpid(-1,&status,0);
        printf("Filho filho %d terminou.\n",WEXITSTATUS(status));
    }



    return 0;
}