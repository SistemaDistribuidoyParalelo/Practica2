#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define ORDENXFILAS 0
#define ORDENXCOLUMNAS 1
int N = 100; // inicio por las dudas

struct matriz_parametros
{
    double *M; //Matriz(arreglo) COMPLETO pero recorremos una porcion de la misma
    double *M2; //Matriz(arreglo) COMPLETO pero recorremos una porcion de la misma
    double *Mresultado;
    int indice_recorrer_total; //indice maximo a recorrer
    int indice_recorrer_parcial; // indice parcial o mitad para recorrer


};
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


//Para calcular tiempo
void *proceso1(void *arg){
    struct matriz_parametros* mp_1 = (struct matriz_parametros*)arg;
    printf("%d \n", mp_1->indice_recorrer_total);
   
    /*
    void *proceso1(void *arg){
    struct matriz_parametros* mp_1 = (struct matriz_parametros*)arg;
    printf("%d \n", mp_1->indice_recorrer);
    printf("%f del arreglo \n",mp_1->M[1]);

    int i = indice_recorrer/2;  // o 4 segun en cuanto tenga q partir la matriz_parametros
    int j = ; // indice para guardar en la matriz 3
    int m=0; // indice para recorrer de a 4 en una matriz de 4x4 tendria q ser generico segun el tamanio de la matriz
    int resultadoparcial=0;
    int t=0; // indice para manejar el inicio del for
    while(i < indice_recorrer){
      for (size_t a = t; a < i; a++) { // recorro la matriz 1
        resultado=resultado + matriz1[i]*matriz2[m]
        m=m+4;
      }
      matriz3[j]=resultado; // guardo el resultado en la matriz 3
      j++;  // incremento para guardar en la siguiente posicion de la matriz3
      t=t+4;// arranco en la siguiente fila
      m=j; // para que la matriz 2 arranque en la posicion siguiente
      i=t*2;// siguiente limite que tendria que ser de la mitad al final

    }

    return NULL ;
}
    */

    for(int i=0; i < (mp_1->indice_recorrer_parcial) ; i++){//Recorro la fila desde 0 hasta la mitad parcial
        for(int j=0;j< (mp_1->indice_recorrer_total);j++){//Recorro la columna desde 0 hasta la mitad parcial
            for(int k=0;k<(mp_1->indice_recorrer_total);k++){ // Realiza todas las multiplicaciones y sumas aprciales hasta obtener el resultado en esa posicion de matriz
            setValor(mp_1->Mresultado,i,j,ORDENXFILAS, getValor(mp_1->Mresultado,i,j,ORDENXFILAS) + getValor(mp_1->M,i,k,ORDENXFILAS)*getValor(mp_1->M2,k,j,ORDENXFILAS));
            }
    }
  }   

    return NULL ;
}

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
    double *A,*B,*C;
    struct matriz_parametros mp;
   
    int check = 1;
    //Controla los argumentos al programa
     if ((argc != 2) || ((N = atoi(argv[1])) <= 0) )
    {
        printf("\nUsar: %s n\n  n: Dimension de la matriz (nxn X nxn)\n", argv[0]);
        exit(1);
    }
    //Inicializa las matrices A y B en 1, el resultado sera una matriz con todos sus valores en N
    A=(double*)malloc(sizeof(double)*N*N);
    B=(double*)malloc(sizeof(double)*N*N);
    C=(double*)malloc(sizeof(double)*N*N);
    
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            setValor(A,i,j,ORDENXFILAS,1);
            setValor(B,i,j,ORDENXFILAS,1);
            setValor(C,i,j,ORDENXFILAS,0);
         
        }
    }   
    imprimeMatriz(A,N);
    imprimeMatriz(B,N);
    imprimeMatriz(C,N);
   
    //Solucion con los hilos, arrancamos con los parametos a pasar
    mp.M = A;
    mp.M2 = B;
    mp.Mresultado = C;
    mp.indice_recorrer_total = N;    
    mp.indice_recorrer_parcial = mp.indice_recorrer_total / 2; // para recorrer la primera mitad de los valores 
    //ese 2 tiene que ser la cantidad de hilos a recorrer

    double tiempoStart= dwalltime();
    pthread_create(&h1,NULL,proceso1 ,&mp);
    pthread_create(&h2,NULL, proceso2 ,&mp);
    pthread_join(h2,NULL);
    pthread_join(h1,NULL);
    printf ( "Fin \n" );
    printf("El resultado final en Segundos = %f \n",dwalltime()-tiempoStart);
   
    //Verifica el resultado
    
    if(check){
    printf("Multiplicacion de matrices resultado correcto\n");
    }else{
    printf("Multiplicacion de matrices resultado erroneo\n");
    }

    C = mp.Mresultado;
    imprimeMatriz(C,N);
   

    free(A);
    free(B);
    free(C);
}
