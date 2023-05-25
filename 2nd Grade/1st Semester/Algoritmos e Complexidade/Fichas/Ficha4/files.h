#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NV 6


typedef struct aresta{
    int dest;
    int custo;
    struct aresta *prox;
} *LAdj, *GrafoL [NV];

typedef int GrafoM[NV][NV];

GrafoM teste = {
    {0,2,7,0,0,0},
    {0,0,0,1,0,0},
    {0,0,0,0,0,1},
    {5,0,0,0,8,0},
    {3,0,0,0,0,0},
    {4,0,0,3,2,0}
};