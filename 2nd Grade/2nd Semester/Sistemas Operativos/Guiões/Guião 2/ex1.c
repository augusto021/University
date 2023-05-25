#include "files.h"

/* Implemente um programa que imprima o seu identificador de processo e o do seu pai. Comprove –
invocando o comando ps – que o pai do seu processo  e o interpretador de comandos que utilizou para o
executar. */

int main(){
    pid_t pid = getpid();
    pid_t ppid = getppid();
    printf("PID do processo: %d\n",pid);
    printf("PID do processo pai: %d\n",ppid);

}