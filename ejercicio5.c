#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

int *A;
double *B;
int T;
int N;
double dwalltime(){
        double sec;
        struct timeval tv;
        int tiempo = gettimeofday(&tv,NULL);
        sec = tv.tv_sec + tv.tv_usec/1000000.0;
        return sec;
}

void *proceso1(void *arg){
    double suma=0.0;
    int ID = *(int*)arg;
    int tam,ini;
    if(T==2){
    if(ID == 0){tam=N/2;ini=0;}
    else{
      ini=N/2;
      tam=N;
    }}else{
      if(ID == 0){tam=N/4;ini=0;}
      if(ID == 1){tam=N/2;ini=N/4;}
      if(ID == 2){tam=(3*N)/4;ini=N/2;}
      if(ID == 3){tam=N;ini=(3*N)/4;}
    }
        for(int j = ini; j<tam; j++){
            suma=suma + A[j];
        }
        double divi= (double)(tam-ini);
        B[ID]=(suma/divi);

        return NULL;
}


int main (int argc , char * argv []) {


    if ((argc != 3) )
    {
        printf("\nUsar: %s n\n  n: Dimension de la matriz (nxn X nxn)\n", argv[0]);
        exit(1);
    }
    T=atoi(argv[2]);
    N=atoi(argv[1]);
    if ((T== 2)||(T==4)) {
      printf("Se van a utilizar %d Hilos \n",T );
    //DECLARACION DE VARIABLES
    pthread_t misHilos[T];
    int threads_ids[T];

    //RESERVA DE MEMORIA DE VECTORES
    A=(int*)malloc(sizeof(int)*N);
    B=(double*)malloc(sizeof(double)*T);


    //  INICIALIZACION DE VECTORES

    for(int i=0; i<N;i++){
        A[i] = rand() % N;
        printf("%d ", A[i]);
    }
    // INICIALIZACION DE HILOS
    double tiempoStart= dwalltime();
    for(int id=0;id<T;id++){
        threads_ids[id] = id;
        pthread_create(&misHilos[id],NULL,proceso1,(void*)&threads_ids[id]);
    }
       for(int i = 1; i<T;i++){
           pthread_join(misHilos[i],NULL);
      }
      printf("\n" );
      printf("El resultado final en Segundos = %f \n",dwalltime()-tiempoStart);
      //ANALISIS DE RESULTADOS
      double resultado=0.0;
      for (int i = 0; i < T; i++) {
        resultado+=B[i];
      }
    double promedio = (resultado/T);
    printf("el promedio es %f\n",promedio );
    printf("\n");

    return 1;
}

}
