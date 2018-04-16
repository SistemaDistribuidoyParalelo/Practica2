#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>


struct tipo{
  int max;
  int min;
};
int *A;
struct tipo *B;
int T;
int N;




//Para calcular tiempo
void *proceso1(void *arg){
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
    for( int i= ini;i<tam;i++){
      if(A[i]  > B[ID].max ) //busco maximo
        {
            B[ID].max = A[i];
        }
        if(A[i] < B[ID].min  ) //busco minimo

            {
                B[ID].min = A[i];

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
  B=(struct tipo*)malloc(sizeof(struct tipo)*T);


  //  INICIALIZACION DE VECTORES
  for (int j = 0; j < T; j++) {
      B[j].max=-1;
      B[j].min=9999;
    /* code */
  }
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


    //ANALISIS DE RESULTADO
    int min=9999;
    int max=-1;
    for (int i = 0; i < T; i++) {
      if (B[i].max > max) {
          max=B[i].max;
      }
      if (B[i].min < min) {
          min=B[i].min;
      }
    }
    printf("El minimo es %d y el maximo es %d\n",min,max );


    free(A);
    free(B);

}
}
