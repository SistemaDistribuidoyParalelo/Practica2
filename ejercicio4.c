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

};

void *proceso1(void *arg){
    int indiceMinimo =0;
    int auxM;
    int valorMinimo = 9999999;
    struct matriz_parametros *mp = (struct matriz_parametros *)arg;
    
    for(int i=0; i<mp->tamParcial;i++){
        //Recorremos ordenando todo
        indiceMinimo = i; 
        valorMinimo = 9999999;
        for(int j = i; j<mp->tamParcial; j++){
            if(mp->V[j] < valorMinimo){
                valorMinimo = mp->V[j];
                indiceMinimo = j;
            }                   
        }
        auxM = mp->V[i];
        mp->V[i] = mp->V[indiceMinimo];
        mp->V[indiceMinimo] = auxM;
       
    }
        return NULL;
} 


void *proceso2(void *arg){
    int indiceMinimo =0;
    int auxM;
    int valorMinimo = 9999999;
    struct matriz_parametros *mp = (struct matriz_parametros *)arg;
    
    for(int i=mp->tamParcial; i<mp->tam;i++){
        //Recorremos ordenando todo
        indiceMinimo = i; 
        valorMinimo = 9999999;
        for(int j = i; j<mp->tam; j++){
            if(mp->V[j] < valorMinimo){
                valorMinimo = mp->V[j];
                indiceMinimo = j;
            }                   
        }
        auxM = mp->V[i];
        mp->V[i] = mp->V[indiceMinimo];
        mp->V[indiceMinimo] = auxM;
       
    }
        return NULL;
}

int main (int argc , char * argv []) {
    pthread_t h1 ;
    pthread_t h2 ;
    int *A,*B;
    int N;
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
    pthread_create(&h1,NULL,proceso1 ,&mp);
    pthread_create(&h2,NULL, proceso2 ,&mp);
    pthread_join(h1,NULL);
    pthread_join(h2,NULL);
    for(int i=0; i<N;i++){
        printf("%d ", mp.V[i]);
    }
    printf("\n");
    
    //Hasta aca funciona sin merge
    int recorridoI = 0 ;
    int recorridoJ = mp.tamParcial;
    int pos = 0;
    while((recorridoI <= mp.tamParcial ) && (recorridoJ <= mp.tam)){
        if(mp.V[recorridoI] <= mp.V[recorridoJ]){
            B[pos] = mp.V[recorridoI];
            recorridoI++;
        }else{
            B[pos] = mp.V[recorridoJ];
            recorridoJ++;
        }
        pos++;
    }
    
    
    for(int i=0; i<N;i++){
        printf("%d ", mp.V[i]);
    }
    printf("\n");
    return 1;
}