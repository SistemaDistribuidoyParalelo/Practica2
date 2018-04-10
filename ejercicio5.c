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
    double *C;
};

void *proceso1(void *arg){

    struct matriz_parametros *mp = (struct matriz_parametros *)arg;
        int suma1=0;
        for(int j = 0; j<mp->tamParcial; j++){
            suma1=suma1+mp->V[j];
        }
        double res = (double)suma1;
        double divi= (double)mp->tamParcial;
        double fin=(res/divi);
        mp->C[0]=fin;

        return NULL;
}


void *proceso2(void *arg){
    struct matriz_parametros *mp = (struct matriz_parametros *)arg;
        int suma2=0;
        for(int i=mp->tamParcial; i<mp->tam;i++){
            suma2=suma2+mp->V[i];

        }
        double res = (double)suma2;
        double divi= (double)mp->tamParcial;
        double fin=(res/divi);
        mp->C[1]=fin;


        return NULL;
}

int main (int argc , char * argv []) {
    pthread_t h1 ;
    pthread_t h2 ;
    int *A;
    double *B;
    int N;
    struct matriz_parametros mp;

    if ((argc != 2) || ((N = atoi(argv[1])) <= 0) )
    {   printf("%d\n",argv[1] );
        printf("\nUsar: %s n\n  n: Dimension de la matriz (nxn X nxn)\n", argv[0]);
        exit(1);
    }

    //Inicio del arreglo
    A=(int*)malloc(sizeof(int)*N);
    B=(double*)malloc(sizeof(double)*1);

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
    pthread_create(&h1,NULL,proceso1 ,&mp);
    pthread_create(&h2,NULL, proceso2 ,&mp);
    pthread_join(h1,NULL);
    pthread_join(h2,NULL);
    double resultado = ((mp.C[0]+mp.C[1]));
    double dividirTam= (double)2;
    double promedio = (resultado/dividirTam);
    printf("el promedio es %f\n",promedio );
    printf("\n");
    return 1;
}
