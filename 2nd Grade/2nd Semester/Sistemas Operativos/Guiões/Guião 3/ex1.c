#include "files.h"

/* Implemente um programa que execute o comando ls -l. Note que no caso da execução ser bem
sucedida, mais nenhuma outra instrução é executada do programa original. */


int main(int argc,const char* argv[]){
    int ret;
    ret = execl("/bin/ls","ls","-l",NULL);
    printf("Erro. Resultado do ret = %d\n", ret);

    return 0;
}