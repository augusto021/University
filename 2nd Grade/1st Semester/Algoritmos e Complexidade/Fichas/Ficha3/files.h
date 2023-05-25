#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define HEAP1_SIZE 17
#define MAX 100

typedef struct pQueue{
    int valores[MAX];
    int tamanho;
} PriorityQueue;


typedef int TreeEntry;

typedef enum balancefactor {LH, EH, RH} BalanceFactor;

struct treenode{
    BalanceFactor bf;
    TreeEntry entry;
    struct treenode *left;
    struct treenode *right;
};

typedef struct treenode *Tree;