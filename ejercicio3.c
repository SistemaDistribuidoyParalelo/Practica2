#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

struct matriz_parametros
{
    double *M; //Matriz(arreglo) COMPLETO pero recorremos una porcion de la misma
    double *variablesGuardar;
    int indice_recorrer_total; //indice maximo a recorrer
    int indice_recorrer_parcial; // indice parcial o mitad para recorrer

};

//Para calcular tiempo
void *proceso1(void *arg){
    struct matriz_parametros* mp_1 = (struct matriz_parametros*)arg;
    
    for(int i = 0;i<mp_1->indice_recorrer_parcial;i++){
        if(mp_1->variablesGuardar[0] < mp_1->M[i] ) //busco maximo
        {
            mp_1->variablesGuardar[0] = mp_1->M[i];
        }
        if(mp_1->variablesGuardar[1] > mp_1->M[i] ) //busco minimo
            {
                mp_1->variablesGuardar[1] = mp_1->M[i];
            }
        
    }
    return NULL ;
}

void *proceso2(void *arg){
    struct matriz_parametros* mp_1 = (struct matriz_parametros*)arg;

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
    int N;
    int check = 1;
    //Controla los argumentos al programa
     if ((argc != 2) || ((N = atoi(argv[1])) <= 0) )
    {
        printf("\nUsar: %s n\n  n: Dimension de la matriz (nxn X nxn)\n", argv[0]);
        exit(1);
    }
    //Inicializa las matrices A y B en 1, el resultado sera una matriz con todos sus valores en N
    A=(double*)malloc(sizeof(double)*N);
    B=(double*)malloc(sizeof(double)*4); //Para guardar las variables de maximos y minimos
    for(int i=0;i<N;i++){
        A[i] = rand() % N;
        printf("%f    ",A[i]);
    }   

    printf("\n");
    B[0] = -1;
    B[1] = 99999;
    
    mp.M = A;
    mp.variablesGuardar = B;
    mp.indice_recorrer_total = N;    
    mp.indice_recorrer_parcial = mp.indice_recorrer_total / 2; // para recorrer la primera mitad de los valores 
    //ese 2 tiene que ser la cantidad de hilos a recorrer

    double tiempoStart= dwalltime();
    pthread_create(&h1,NULL,proceso1 ,&mp);
    //pthread_create(&h2,NULL, proceso2 ,&mp);
    //pthread_join(h2,NULL);
    pthread_join(h1,NULL);
    printf ( "Fin \n" );
    printf("El resultado final en Segundos = %f \n",dwalltime()-tiempoStart);
    printf("%f    ",mp.variablesGuardar[0]);
    printf("%f    \n",mp.variablesGuardar[1]);


    //Verifica el resultad
    free(A);
    free(B);
    
}
