#include "files.h"

/*
Uma min-heap é uma árvore binária em que cada nodo é menor ou igual a todos os seus
sucessores.
Por outro lado, uma árvore diz-se semi-completa se todos os nı́veis da árvore estão completos,
com a possı́vel excepção do último, que pode estar parcialmente preenchido (da esquerda para
a direita).
As árvores semi-completas têm uma representação ”económica” em array: os nodos são ar-
mazenados por nı́vel, sempre da esquerda para a direita.
*/

void printHeap(int *heap){
    for(int i = 0,j = 1;i < HEAP1_SIZE;i++,j++){
        printf("Heap nível %d: %d\n",j,heap[i]);
    }
}

void swap(int h[],int xp,int yp){
    int temp = h[xp];
    h[xp] = h[yp];
    h[yp] = temp;

}

int heap_pop(int h[],int N){
    swap(h,0,N-1);
    bubbleDown(0,h,N-1);
    return h[N-1];
}


// -------------- Exercício 1 -------------- //
int heap1A(int p){
    return 2 * p + 1;
}

int heap1B(int p){
    return 2 * p + 2;
}

int heap1C(int p){
    return (p-1)/2;
}
// ------------------------------------------ //

// -------------- Exercício 2 -------------- //
void bubbleUp(int i,int h[]){
    while(i > 0 && h[i] < h[heap1C(i)]){
        swap(h,i,heap1C(i));
        i = heap1C(i);
    }
}
// ------------------------------------------ //

// -------------- Exercício 3 -------------- //

void bubbleDown(int i,int h[],int N){
    while((heap1A(i) < N && h[i] > h[heap1A(i)]) || (heap1B(i) < N && h[i] > h[heap1B(i)])){
        if(heap1B(i) >= N || h[heap1A(i)] < h[heap1B(i)]){
            swap(h,i,heap1A(i));
            i = heap1A(i);
        }
        else {
            swap(h,i,heap1B(i));
            i = heap1B(i);
        }
    }

}

// ------------------------------------------ //

// -------------- Exercício 4 -------------- //

void empty(PriorityQueue *q){
    free(q);
}

int isEmpty(PriorityQueue *q){
    return q->tamanho;
}

int add(int x,PriorityQueue *q){
    if(q->tamanho == MAX) return 1;

    q->valores[q->tamanho] = x;
    bubbleUp(q->tamanho,q->valores);
    q->tamanho++;

    return 0;
}

int remove(PriorityQueue *q,int *rem){
    if(q->tamanho == 0) return 1;

    *rem = q->valores[0];
    q->valores[0] = q->valores[q->tamanho - 1];
    q->tamanho--;
    bubbleDown(0,q->valores,q->tamanho);

    return 0;
}

// ------------------------------------------ //

// -------------- Exercício 5 -------------- //

//Top-Down
void heapify1(int v[],int N){
    for(int i = 0;i < N;i++){
        bubbleUp(i,v);
    }

}

// Bottom-Up
void heapify2(int v[],int N){
    for(int i = N - 1;i > -1;i--){
        bubbleDown(i,v,N);
    }
}

// ------------------------------------------ //

// -------------- Exercício 6 -------------- //

void ordenaHeap(int h[],int N){
    for(int i = 1;i < N;i++){
        swap(h,0,N-i);
        bubbleDown(0,h,N-i);
    }
}

// ------------------------------------------ //

// -------------- Exercício 7 -------------- //

int* sequencia(int v[],int N,int k){
    int *aux;
    aux = (int*)malloc(k * sizeof(int));
    for(int i = 0;i < k;i++){
        aux[i] = v[i];
    }
    heapify1(aux,k);

    for(int i = k; i < N;i++){
        if(v[i] > aux[0]){
            heap_pop(aux,k);
            aux[k-1] = v[i];
            bubbleUp(k-1,aux);

        }
    }
    return aux;
}

// ------------------------------------------ //

int main(){
    int *heap;

    // -------------- Inicializar heap -------------- //
    heap = (int*)malloc(HEAP1_SIZE * sizeof(int));

    heap[0] = 10;
    heap[1] = 15;
    heap[2] = 11;
    heap[3] = 16;
    heap[4] = 22;
    heap[5] = 35;
    heap[6] = 20;
    heap[7] = 21;
    heap[8] = 23;
    heap[9] = 34;
    heap[10] = 37;
    heap[11] = 80;
    heap[12] = 43;
    heap[13] = 22;
    heap[14] = 25;
    heap[15] = 24;
    heap[16] = 28;

    printf("\nHeap incializada!\n\n");
    // ----------------------------//

    printHeap(heap);
    // printf("\nSub-árvore da esqueda do nodo da posição 4: %d\n",heap1A(4));
    // printf("\nSub-árvore da direita do nodo da posição 6: %d\n",heap1A(6));


    free(heap);    
    return 0;
}