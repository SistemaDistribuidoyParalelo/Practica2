#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define ORDENXFILAS 1
#define ORDENXCOLUMNAS 0
int N=100;

struct matriz_parametros
{
    double *M; //Matriz(arreglo) COMPLETO pero recorremos una porcion de la misma
    int indice_recorrer; //indice maximo a recorrer

};

//Para calcular tiempo
void *proceso1(void *arg){
    struct matriz_parametros* mp_1 = (struct matriz_parametros*)arg;
    printf("%d \n", mp_1->indice_recorrer);
    printf("%f del arreglo \n",mp_1->M[1]);
    return NULL ;
}

void *proceso2(void *arg){
    struct matriz_parametros* mp_1 = (struct matriz_parametros*)arg;
    printf("%d \n", mp_1->indice_recorrer);
    return NULL ;
}

//Retorna el valor de la matriz en la posicion fila y columna segun el orden que este ordenada
double getValor(double *matriz,int fila,int columna,int orden){
 if(orden==ORDENXFILAS){
  return(matriz[fila*N+columna]);
 }else{
  return(matriz[fila+columna*N]);
 }
}

//Establece el valor de la matriz en la posicion fila y columna segun el orden que este ordenada
void setValor(double *matriz,int fila,int columna,int orden,double valor){
 if(orden==ORDENXFILAS){
  matriz[fila*N+columna]=valor;
 }else{
  matriz[fila+columna*N]=valor;
 }
}

double dwalltime(){
        double sec;
        struct timeval tv;
        int tiempo = gettimeofday(&tv,NULL);
        sec = tv.tv_sec + tv.tv_usec/1000000.0;
        return sec;
}

int main ( int argc , char * argv []) {
    //declaraciones
    pthread_t h1 ;
    pthread_t h2 ;
    double *A,*B;
    struct matriz_parametros mp;
    int N = 100; // inicio por las dudas
    
    //Controla los argumentos al programa
     if ((argc != 2) || ((N = atoi(argv[1])) <= 0) )
    {
        printf("\nUsar: %s n\n  n: Dimension de la matriz (nxn X nxn)\n", argv[0]);
        exit(1);
    }
    //Inicializa las matrices A y B en 1, el resultado sera una matriz con todos sus valores en N
    A=(double*)malloc(sizeof(double)*N*N);
    B=(double*)malloc(sizeof(double)*N*N);
    
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            setValor(A,i,j,ORDENXFILAS,1);
            setValor(B,i,j,ORDENXFILAS,1);
        }
    }   
    //Solucion con los hilos, arrancamos con los parametos a pasar

    mp.M = A;
    mp.indice_recorrer = N/2;    

    double tiempoStart= dwalltime();
    pthread_create(&h1,NULL,proceso1 ,&mp);
    pthread_create(&h2,NULL, proceso2 ,&mp);
    pthread_join(h2,NULL);
    pthread_join(h1,NULL);
    printf ( "Fin \n" );
    printf("El resultado final en Segundos = %f \n",dwalltime()-tiempoStart);
    free(A);
    free(B);
}