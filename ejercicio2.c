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

};

int proceso1(void *arg){
    int cant=0;
    struct matriz_parametros *mp = (struct matriz_parametros *)arg;

    for(int i=0; i<mp->tamParcial;i++){
        //Recorremos ordenando todo
        for(int j = i; j<mp->tamParcial; j++){
            if(mp->V[j] == mp->valor){
                cant++;
            }
        }

    }
        return cant;
}


int proceso2(void *arg){
    int cant1=0;
    struct matriz_parametros *mp = (struct matriz_parametros *)arg;

    for(int i=0; i<mp->tamParcial;i++){
        //Recorremos ordenando todo
        for(int j = i; j<mp->tamParcial; j++){
            if(mp->V[j] == mp->valor){
                cant1++;
            }
        }

    }
        return cant1;
}

int main (int argc , char * argv []) {
    pthread_t h1 ;
    pthread_t h2 ;
    int *A,*B;
    int N,cant1,cant2;
    struct matriz_parametros mp;

    if ((argc != 2) || ((N = atoi(argv[1])) <= 0) )
    {
        printf("\nUsar: %s n\n  n: Dimension de la matriz (nxn X nxn)\n", argv[0]);
        exit(1);
    }

    //Inicio del arreglo
    A=(int*)malloc(sizeof(int)*N);
    B=(int*)malloc(sizeof(int)*N);

    for(int i=0; i<N;i++){
        A[i] = rand() % N;
        printf("%d ", A[i]);
    }
    printf("\n");
    // Cargamos estructura para usar en los hilos
    mp.V = A;
    mp.tam = N;
    mp.tamParcial = N/2; // dividido 2 por la cantidad de hilos
    mp.valor= atoi(argv[2]);
    pthread_create(&h1,NULL,proceso1 ,&mp);
    pthread_create(&h2,NULL, proceso2 ,&mp);
    pthread_join(h1,&cant1);
    pthread_join(h2,&cant2);

    printf("La cantidad de veces que aparece el numero %d es %d ",mp.valor,*cant1+*cant2 );
    printf("\n");
    return 1;
}
