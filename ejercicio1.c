#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

//Para calcular tiempo
void *proceso1(void *arg){
    char *msg ="Hola" ;
    int i ;
    for (i=0;i<strlen(msg);i++) {
    printf("%c ", msg[ i ]) ;
    fflush(stdout) ;
    usleep(100000) ;
    }
    return NULL ;
}

void *proceso2(void *arg){
    char * msg = " mundo " ;
    int i;
    for ( i=0 ; i<strlen(msg); i++ ) {
    printf(" %c " , msg [ i ]) ;
    fflush(stdout) ;
    usleep(100000) ;
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
    pthread_t h1 ;
    pthread_t h2 ;
    char * hola = "Hola" ;
    char * mundo = "mundo" ;
    double tiempoStart= dwalltime();
    pthread_create(&h1,NULL,proceso1 ,(void *)hola);
    pthread_join(h1,NULL);
    pthread_create(&h2,NULL, proceso2 ,(void *)mundo);
    pthread_join(h2,NULL);
    printf ( "Fin \n" );

    printf("El resultado final en Segundos = %f",dwalltime()-tiempoStart);

}