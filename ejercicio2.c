#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

struct matriz_parametros

{
    int *V;
    int tam;
    int tamParcial;
    int valor;
    int *C;
};

void *proceso1(void *arg){

    struct matriz_parametros *mp = (struct matriz_parametros *)arg;

        for(int j = 0; j<mp->tamParcial; j++){
            if(mp->V[j] == mp->valor){
                mp->C[0]++;
            }
        }


        return NULL;
}


void *proceso2(void *arg){
    struct matriz_parametros *mp = (struct matriz_parametros *)arg;

        for(int i=mp->tamParcial; i<mp->tam;i++){
            if(mp->V[i] == mp->valor){
                mp->C[1]++;
            }
        }


        return NULL;
}

int main (int argc , char * argv []) {
    pthread_t h1 ;
    pthread_t h2 ;
    int *A,*B;
    int N;
    struct matriz_parametros mp;

    if ((argc != 3) || ((N = atoi(argv[1])) <= 0) )
    {   printf("%d\n",argv[1] );
        printf("\nUsar: %s n\n  n: Dimension de la matriz (nxn X nxn)\n", argv[0]);
        exit(1);
    }

    //Inicio del arreglo
    A=(int*)malloc(sizeof(int)*N);
    B=(int*)malloc(sizeof(int)*1);
    B[0]=0;
    B[1]=0;

    for(int i=0; i<N;i++){
        A[i] = rand() % N;
        printf("%d ", A[i]);
    }
    printf("\n");
    // Cargamos estructura para usar en los hilos
    mp.V = A;
    mp.C = B;
    mp.tam = N;
    mp.tamParcial = N/2; // dividido 2 por la cantidad de hilos
    mp.valor= atoi(argv[2]);
    pthread_create(&h1,NULL,proceso1 ,&mp);
    pthread_create(&h2,NULL, proceso2 ,&mp);
    pthread_join(h1,NULL);
    pthread_join(h2,NULL);
    int resultado = mp.C[0]+mp.C[1];
    printf("la cantidad de veces que aparece el numero %d es %d\n",mp.valor,resultado );
    printf("\n");
    return 1;
}
