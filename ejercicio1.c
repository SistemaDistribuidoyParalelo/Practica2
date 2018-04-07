#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void *proceso1(void *arg){
    char *msg ="Hola" ;
    int i ;
    for (i=0;i<strlen(msg);i++) {
    printf("%c ", msg[ i ]) ;
    fflush(stdout) ;
    usleep(1000000) ;
    }
    return NULL ;
}

void *proceso2(void *arg){
    char * msg = " mundo " ;
    int i;
    for ( i=0 ; i<strlen(msg); i++ ) {
    printf(" %c " , msg [ i ]) ;
    fflush(stdout) ;
    usleep(1000000) ;
    }
    return NULL ;

}

int main ( int argc , char * argv []) {
pthread_t h1 ;
pthread_t h2 ;
char * hola = "Hola" ;
char * mundo = "mundo" ;
pthread_create(&h1,NULL,proceso1 ,(void *)hola);
pthread_join(h1,NULL);
pthread_create(&h2,NULL, proceso2 ,(void *)mundo);
pthread_join(h2,NULL);
printf ( "Fin \n" ) ;
}