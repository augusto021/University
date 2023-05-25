#include "files.h"
#define Size 5

/*
Nos exercícios seguintes pretende-se usar uma tabela de Hash para implementar multi-conjuntos
de strings. Para cada string deve ser guardado o número de vezes que ela ocorre no multiconjunto. As operações em causa são por isso:
• inicialização de um multi-conjunto a vazio
• adição de um elemento a um multi-conjunto
• teste de pertença (saber qual a multplicidade de um elemento num multi-conjunto)
• remoção de uma ocorrência de um elemento de um multi-conjunto
Vamos por isso assumir a existência de uma função unsigned hash (char chave), como
por exemplo a seguinte (http://www.cse.yorku.ca/~oz/hash.html)
*/

unsigned hash(char *str){
    unsigned hash = 5381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c;   /* hash * 33 + c */
    return hash % Size;
}


typedef struct nodo{
    char *chave; int ocorr;
    struct nodo *prox;
} Nodo, *THash[Size];


void printHash(THash t,int n){
    THash aux;
    for(int i = 0;i < n;i++){
        for(aux[i] = t[i];aux[i] != NULL;aux[i] = aux[i]->prox){
            printf("STRING: %s \n",aux[i]->chave);
            printf("OCORR: %d \n",aux[i]->ocorr);
            printf("\n");
        }
    }
}

// -------------- Exercício 1 -------------- //

void initEmpty(THash t){
    for(int i = 0;i < Size;i++){
        t[i] = NULL;
    }
}

// ------------------------------------------ //

// -------------- Exercício 2 -------------- //

void add(char *s,THash t){
    int ind = hash(s);
    if(ind >= Size) return;

    Nodo** aux;
    for(aux=&(t[ind]);*aux != NULL;aux = &(*aux)->prox){
        if(!strcmp(s,(*aux)->chave)){
            (*aux)->ocorr++;
            return;
        }
    }
    (*aux) = malloc(sizeof(struct nodo));
    (*aux)->chave = s;
    (*aux)->ocorr = 1;
}

// ------------------------------------------ //

// -------------- Exercício 3 -------------- //

int lookup(char *s,THash t){
    int ind = hash(s);
    Nodo** aux;
    for(aux = &(t[ind]);*aux != NULL;aux = &(*aux)->prox){
        if(!strcmp((*aux)->chave,s)){
            return ((*aux)->ocorr);
        }
    } 
    return 0;
}

// ------------------------------------------ //

// -------------- Exercício 4 -------------- //

int remover(char *s,THash t){
    int ind = hash(s);
    Nodo** aux;
    for(aux = &(t[ind]);*aux = NULL;aux = &(*aux)->prox){
        if(!strcmp((*aux)->chave,s)){
            (*aux)->ocorr--;
            if((*aux)->ocorr == 0){
                Nodo* temp = *aux;
                *aux = (*aux)->prox;
                free(temp);
                return 0;
            }
            else return (*aux)->ocorr;
        }
    }
    return -1;
}

// ------------------------------------------ //

int main(){
    THash t;
    initEmpty(t);
    add("ola",t);
    add("adeus",t);
    add("yuh",t);
    add("ola",t);
    add("ola",t);
    //remover("yuh",t);
    printHash(t,3);
    return 0;
}