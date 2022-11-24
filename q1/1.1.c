#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>
#include <time.h>

struct sched_param p1,p2,p3;

pthread_t t1,t2,t3;

void* countA(){
    p1.sched_priority = 0;
    pthread_setschedparam(pthread_self(), SCHED_OTHER, &p1);
    nice(0);
    for(long long int i=0;i<(4294967296L);i++){

    }
}

void* countB(){
    p2.sched_priority = 90;
    pthread_setschedparam(pthread_self(), SCHED_RR, &p2);
    
    for(long long int i=0;i<(4294967296L);i++){
        
    }
    
}

void* countC(){
    p3.sched_priority = 90;
    pthread_setschedparam(pthread_self(), SCHED_FIFO, &p3);
    for(long long int i=0;i<(4294967296L);i++){
        
    }
    
}

int main(){

    
    struct timespec start1, stop1, start2, stop2, start3, stop3; 

    clock_gettime( CLOCK_REALTIME, &start1);
    pthread_create(&t1, NULL, &countA, NULL);

    clock_gettime( CLOCK_REALTIME, &start2);
    pthread_create(&t2, NULL, &countB, NULL);

    clock_gettime( CLOCK_REALTIME, &start3);
    pthread_create(&t3, NULL, &countC, NULL);

    pthread_join(t1, NULL);
    clock_gettime( CLOCK_REALTIME, &stop1);

    pthread_join(t2, NULL);
    clock_gettime( CLOCK_REALTIME, &stop2);
    
    pthread_join(t3, NULL);
    clock_gettime( CLOCK_REALTIME, &stop3);
   

    if(stop1.tv_nsec - start1.tv_nsec < 0L){
        stop1.tv_sec -= 1;
        stop1.tv_nsec += 1000000000L;
    }
    if(stop2.tv_nsec - start2.tv_nsec < 0L){
        stop2.tv_sec -= 1;
        stop2.tv_nsec += 1000000000L;
    }
    if(stop3.tv_nsec - start3.tv_nsec < 0L){
        stop3.tv_sec -= 1;
        stop3.tv_nsec += 1000000000L;
    }

    printf("%d.%ld seconds\n", stop1.tv_sec - start1.tv_sec, stop1.tv_nsec - start1.tv_nsec);
    printf("%d.%ld seconds\n", stop2.tv_sec - start2.tv_sec, stop2.tv_nsec - start2.tv_nsec);
    printf("%d.%ld seconds\n", stop3.tv_sec - start3.tv_sec, stop3.tv_nsec - start3.tv_nsec);

}