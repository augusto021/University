#include "files.h"
#define Size 10
#define Free 0
#define Used 1
#define Del 2

typedef struct bucket{
    int status; // Free | Used | Del
    char *chave;
    int ocorr;
} THash[Size];

unsigned hash(char *str){
    unsigned hash = 5381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c;   /* hash * 33 + c */
    return hash % Size;
}

// -------------- Exercício 1 -------------- //

int where(char *s,THash t){
    return hash(s);
}

// ------------------------------------------ //

// -------------- Exercício 2a -------------- //

void initEmpty(THash t){
    for(int i = 0;i < Size;i++){
        t[i].status = Free;
        t[i].chave = NULL;
        t[i].ocorr = 0;
    }
}

// ------------------------------------------ //

// -------------- Exercício 2b -------------- //