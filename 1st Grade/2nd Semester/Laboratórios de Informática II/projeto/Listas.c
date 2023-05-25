/**
@file Lista.c
Definição das funções com listas ligadas.
*/
#include "Listas.h"
#include "Logicadoprograma.h"
#include <stdlib.h>
#include "stdio.h"

/**========================================MÓDULO DAS LISTAS LIGADAS==================================================*/

/** Cria uma lista vazia.*/
LISTA criar_lista(){
    LISTA lista;
    lista = NULL;
    return lista;
}

/** Insere um valor na cabeça da lista.*/
LISTA insere_cabeca(LISTA L, void *valor){
    LISTA l = malloc(sizeof(Nodo));

    l->variavel = valor;
    l->prox = L;
    return l;
}

/** Devolve a cabeça da lista.*/
void *devolve_cabeca(LISTA L){
    return (L->variavel);
}

/** Devolve a cauda da lista.*/
LISTA proximo(LISTA L){
    return (L->prox);
}

/** Remove a cabeça da lista (libertando o espaço ocupado) e devolve a cauda.*/
LISTA remove_cabeca(LISTA L){
    LISTA temp;
    temp = L->prox;
    free(L);
    return (temp);
}

/** Devolve verdareiro se a lista é vazia.*/
int lista_esta_vazia(LISTA L){
    if (L == NULL)
        return 1;
    return 0;
}

/** Indica o comprimento de uma lista.*/
int length_lista(LISTA L){
    int i;
    for(i=0;!lista_esta_vazia(L);i++)
        L = L->prox;
    return i;
}

/** Função que cria a lista de casas vazia a volta da peça branca.*/
LISTA armazena_branca(ESTADO *e, COORDENADA c) {
    int x, y;
    LISTA l = criar_lista();

    x = c.linha;
    y = c.coluna;
    COORDENADA *l1 = malloc(sizeof(COORDENADA));
    COORDENADA *l2 = malloc(sizeof(COORDENADA));
    COORDENADA *l3 = malloc(sizeof(COORDENADA));
    COORDENADA *l4 = malloc(sizeof(COORDENADA));
    COORDENADA *l5 = malloc(sizeof(COORDENADA));
    COORDENADA *l6 = malloc(sizeof(COORDENADA));
    COORDENADA *l7 = malloc(sizeof(COORDENADA));
    COORDENADA *l8 = malloc(sizeof(COORDENADA));

    l1->linha = x - 1;
    l1->coluna = y - 1;
    l2->linha = x;
    l2->coluna = y - 1;
    l3->linha = x + 1;
    l3->coluna = y - 1;
    l4->linha = x + 1;
    l4->coluna = y;
    l5->linha = x + 1;
    l5->coluna = y + 1;
    l6->linha = x;
    l6->coluna = y + 1;
    l7->linha = x - 1;
    l7->coluna = y + 1;
    l8->linha = x - 1;
    l8->coluna = y;

    if (casa_livre(e, *l1) == 1) l = insere_cabeca(l, l1);
    else free(l1);
    if (casa_livre(e, *l2) == 1) l = insere_cabeca(l, l2);
    else free(l2);
    if (casa_livre(e, *l3) == 1) l = insere_cabeca(l, l3);
    else free(l3);
    if (casa_livre(e, *l4) == 1) l = insere_cabeca(l, l4);
    else free(l4);
    if (casa_livre(e, *l5) == 1) l = insere_cabeca(l, l5);
    else free(l5);
    if (casa_livre(e, *l6) == 1) l = insere_cabeca(l, l6);
    else free(l6);
    if (casa_livre(e, *l7) == 1) l = insere_cabeca(l, l7);
    else free(l7);
    if (casa_livre(e, *l8) == 1) l = insere_cabeca(l, l8);
    else free(l8);

    return l;
}

/**===================================================================================================================*/

