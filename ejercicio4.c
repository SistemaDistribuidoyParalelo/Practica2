#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>


    int *V;
    int *B;
    int N;
    int T;
    double dwalltime(){
            double sec;
            struct timeval tv;
            int tiempo = gettimeofday(&tv,NULL);
            sec = tv.tv_sec + tv.tv_usec/1000000.0;
            return sec;
    }

void *proceso1(void *arg){
    int indiceMinimo =0;
    int auxM;
    int valorMinimo = 9999999;
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

    for(int i=ini; i<tam;i++){
        //Recorremos ordenando todo
        indiceMinimo = i;
        valorMinimo = 9999999;
        for(int j = i; j<tam; j++){
            if(V[j] < valorMinimo){
                valorMinimo = V[j];
                indiceMinimo = j;
            }
        }
        auxM = V[i];
        V[i] = V[indiceMinimo];
        V[indiceMinimo] = auxM;

    }
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
  V=(int*)malloc(sizeof(int)*N);
  B=(int*)malloc(sizeof(int)*T);
  //  INICIALIZACION DE VECTORES

  for(int i=0; i<N;i++){
      V[i] = rand() % N;
      printf("%d ", V[i]);
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


    //Hasta aca funciona sin merge
    int recorridoI = 0 ;
    int recorridoJ = N/T;
    int pos = 0;
    int recorridoparcial=N/T;
    while((recorridoI < recorridoparcial ) && (recorridoJ < N)){
        if(V[recorridoI] <= V[recorridoJ]){
            B[pos] = V[recorridoI];
            recorridoI++;
            pos++;
        }else{
            B[pos] = V[recorridoJ];
            recorridoJ++;
            pos++;

        }
    }
    while (recorridoI < recorridoparcial) {
    B[pos] = V[recorridoI];
    pos++;
    recorridoI++;
    }
    while (recorridoJ < N) {
    B[pos] = V[recorridoJ];
    pos++;
    recorridoJ++;
    }
    for(int i=0; i<N;i++){
        printf("%d ", B[i]);
    }
    printf("\n");
    return 1;
}}
