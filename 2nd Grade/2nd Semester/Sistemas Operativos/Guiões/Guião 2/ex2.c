#include "files.h"

/* Implemente um programa que crie um processo filho. Pai e filho devem imprimir o seu identificador de
processo e o do seu pai. O pai deve ainda imprimir o PID do seu filho. */


int main(int argc,const char* argv[]){
    pid_t pid;
    int status;

    if((pid = fork()) == 0){
        printf("O PID do filho é %d.\nO PID do respetivo pai é %d.\n",getpid(),getppid());
    }

    else{
        pid_t child = wait(&status);
        printf("O PID do pai é %d.\nO PID do pai do pai é %d.\nO PID do filho do pai inicial é %d.\n",getpid(),getppid(),child);
    }
}