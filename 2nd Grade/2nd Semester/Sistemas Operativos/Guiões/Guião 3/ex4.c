#include "files.h"

/* Implemente uma versão simplificada da função system(). Ao contrário da função original, não tente
suportar qualquer tipo de redireccionamento, ou composição/encadeamento de programas executáveis.
O único argumento deverá ser uma string que especifica um programa executável e uma eventual lista de
argumentos. Procure que o comportamento e valor de retorno da sua função sejam compatíveis com a
original. */

int my_system(const char* arguments){
    char* exec_args[100];
    char* token = strtok((char*) arguments," ");
    int i = 0;
    while(token != NULL){
        exec_args[i++] = strdup(token);
        token = strtok(NULL, " ");
    }

    exec_args[i] = NULL;
    int ret;
    ret = execvp(exec_args[0],exec_args);

    return ret;
}



int main(int argc,const char* argv[]){
    int ret = my_system(argv[1]);
    return 0;
}