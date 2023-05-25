#include "files.h"

void initGrafoL(GrafoL gl){
    int i;
    for(i = 0;i < NV;i++){
        gl[i] = NULL;
    }
}

int maxArray(int array[],int N){
    int res = 0;
    int max = array[0];

    for(int i = 1;i < N;i++){
        if(max < array[i]) max = array[i];
    }
    return max;
}

void printArray(int array[],int N){
    for(int i = 0;i < NV;i++){
        printf("%d ,",array[i]);
    }
    printf("\n");
}


void printGrafoL(GrafoL g){
    int i;
    LAdj aux;
    for(i = 0;i < NV;i++){
        printf("%d : ",i);
    for(aux = g[i];aux !=NULL;aux = aux->prox)
        printf("%d(%d), ",aux->dest,aux->custo);
    printf("\n");
    }
}


// ------------- Exercício 1 ------------- //

void fromMat(GrafoM in,GrafoL out){
    initGrafoL(out);

    for(int i = 0;i < NV;i++){
        for(int j = 0;j < NV;j++){
            LAdj novo = malloc(sizeof(struct aresta));
            if(in[i][j] > 0){
                novo->dest = j;
                novo->custo = in[i][j];
                novo->prox = out[i];
                out[i] = novo;
            }
        }
    }
}

// --------------------------------------- //

// ------------- Exercício 2 ------------- //

void inverte(GrafoL in,GrafoL out){
    initGrafoL(out);



}

// --------------------------------------- //

// ------------- Exercício 3 ------------- //

int inDegree(GrafoL g){
    int visitados[NV];
    LAdj aux;

    for(int i = 0;i < NV;i++) visitados[i] = 0;

    for(int i = 0;i < NV;i++){
        for(aux = g[i];aux != NULL;aux = aux->prox){
            visitados[aux->dest]++;
        }
    }
    return maxArray(visitados,NV);
}

// --------------------------------------- //

// ------------- Exercício 4 ------------- //

int colorOK(GrafoL g,int cor[]){
    LAdj aux;

    for(int i = 0;i < NV;i++){
        for(aux = g[i];aux != NULL;aux = aux->prox){
            if(cor[i] == cor[aux->dest]){
                return -1;
            }
        } 
    }
    printArray(cor,NV);
    return 0;
}

// --------------------------------------- //

// ------------- Exercício 5 ------------- //

int exists(GrafoL g,int from,int to){
    LAdj aux;

    for(aux = g[from];aux != NULL;aux = aux->prox){
        if(aux->dest == to) return 1;
    }
    return 0;
}

int homomorfOK(GrafoL g,GrafoL h,int f[]){
    LAdj aux;

    for(int i = 0;i < NV;i++){
        for(aux = g[i];aux != NULL;aux = aux->prox){
            if(!exists(g,f[i],f[h[i]->dest])) return 0;
        }
    }
    return 1;
}

// --------------------------------------- //

int main(){
    GrafoL g,g2;
    fromMat(teste,g);
    printGrafoL(g);
    printf("Grau do grafo: %d\n",inDegree(g));
}