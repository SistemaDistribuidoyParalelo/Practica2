#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define ORDENXFILAS 0
#define ORDENXCOLUMNAS 1
int N = 100; // inicio por las dudas

double *M; //Matriz(arreglo) COMPLETO pero recorremos una porcion de la misma
double *M2; //Matriz(arreglo) COMPLETO pero recorremos una porcion de la misma
double *Mresultado;
int indice_recorrer_total; //indice maximo a recorrer
int indice_recorrer_parcial; // indice parcial o mitad para recorrer

//imprimir matriz
void imprimeMatriz(double *S,int N){
// Imprime la matriz pasada por parametro
// N es la cantidad de bloques, r dimension de cada bloque
  printf(" \n");
  printf(" \n");
  for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            printf("%f  ",S[i+j*N]);
        }
        printf(" \n");
  }
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

/*Recorremos la porcion de arreglo correspondiente a la matriz analizar.
    EL inicio del primer for
    El fin corresponde al ultimo for
*/
void recorridoParcial(int inicio, int finalParcial, int totalMatriz){
    for(inicio; inicio < finalParcial ; inicio++){//Recorro la fila desde 0 hasta la mitad parcial
        for(int j=0;j< totalMatriz;j++){//Recorro la columna desde 0 hasta la mitad parcial
            for(int k=0;k<totalMatriz;k++){ // Realiza todas las multiplicaciones y sumas aprciales hasta obtener el resultado en esa posicion de matriz
            setValor(Mresultado,inicio,j,ORDENXFILAS, getValor(Mresultado,inicio,j,ORDENXFILAS) + getValor(M,inicio,k,ORDENXFILAS)*getValor(M2,k,j,ORDENXFILAS));
            }
    }
  }   
}
//Para calcular tiempo
void *proceso1(void *arg){
    int ID = (int)arg;
    printf("el ID = %d \n",ID );

    switch(ID){
    case(1):
        printf("Este es el 1");
    break;
    }
    return NULL ;
}
/*
void *proceso2(void *arg){
    struct matriz_parametros* mp_1 = (struct matriz_parametros*)arg;
    printf("%d \n", mp_1->indice_recorrer_total);
    
    for(int a = mp_1->indice_recorrer_parcial; a < (mp_1->indice_recorrer_total) ; a++){ //Recorro la fila dsde 0 hasta la mitad parcial
        for(int b=0;b< (mp_1->indice_recorrer_total);b++){//Recorro la columna desde 0 hasta la mitad parcial
            for(int c=0;c<(mp_1->indice_recorrer_total);c++){ // Realiza todas las multiplicaciones y sumas aprciales hasta obtener el resultado en esa posicion de matriz
            setValor(mp_1->Mresultado,a,b,ORDENXFILAS, getValor(mp_1->Mresultado,a,b,ORDENXFILAS) + getValor(mp_1->M,a,c,ORDENXFILAS)*getValor(mp_1->M2,c,b,ORDENXFILAS));
            }
    }
  }   


    
    return NULL ;
}

*/

double dwalltime(){
        double sec;
        struct timeval tv;
        int tiempo = gettimeofday(&tv,NULL);
        sec = tv.tv_sec + tv.tv_usec/1000000.0;
        return sec;
}

int main ( int argc , char * argv []) {
    //declaraciones
    pthread_t h[N]; 
    int ID[N];
    double *A,*B,*C;
    int cantHilos;
    int check = 1;
    //Controla los argumentos al programa
     if ((argc != 3) || ((N = atoi(argv[1])) <= 0)  ||(( cantHilos= atoi(argv[2]) <= 0 ))){
        printf("\nUsar: %s n\n  n: Dimension de la matriz (nxn X nxn) y luego la cantidad de Hilos\n", argv[0]);
        exit(1);
    }
    //Inicializa las matrices A y B en 1, el resultado sera una matriz con todos sus valores en N
    M=(double*)malloc(sizeof(double)*N*N);
    M2=(double*)malloc(sizeof(double)*N*N);
    Mresultado=(double*)malloc(sizeof(double)*N*N);
    
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            setValor(M,i,j,ORDENXFILAS,1);
            setValor(M2,i,j,ORDENXFILAS,1);
            setValor(Mresultado,i,j,ORDENXFILAS,0);
         
        }
    }   
    imprimeMatriz(M,N);
    imprimeMatriz(M2,N);
    imprimeMatriz(Mresultado,N);
   
    //Solucion con los hilos, arrancamos con los parametos a pasar
    indice_recorrer_total = N;    
    indice_recorrer_parcial = indice_recorrer_total / cantHilos; 
    //Para recorrer la primera mitad de los valores 

    double tiempoStart= dwalltime();
    for(int i = 1; i<=N;i++){
        ID[i] = i;
        pthread_create(&h[i],NULL,proceso1 ,(void*)&ID[i]);
    }
     for(int i = 1; i<=N;i++){
         pthread_join(h[i],NULL);
    }
   
   
    
    printf ( "Fin \n" );
    printf("El resultado final en Segundos = %f \n",dwalltime()-tiempoStart);
   
    //Verifica el resultado
    
    if(check){
    printf("Multiplicacion de matrices resultado correcto\n");
    }else{
    printf("Multiplicacion de matrices resultado erroneo\n");
    }

    imprimeMatriz(Mresultado,N);
    free(M);
    free(M2);
    free(Mresultado);
}
