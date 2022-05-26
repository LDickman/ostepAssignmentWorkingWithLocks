#include <stdio.h>
#include <pthread.h>
//#include "common_threads.h"

int balance = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* worker(void* arg) {
    pthread_mutex_lock(&lock); ///locks
    balance++; // unprotected access // removing this causes no errors
    pthread_mutex_unlock(&lock); //unlocks
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    pthread_create(&p, NULL, worker, NULL);
    pthread_mutex_lock(&lock);  //locks  // Not having these locks here results in errors
    balance++; // unprotected access
    pthread_mutex_unlock(&lock); // unlocks  /// When having both locks no errors occur
    pthread_join(p, NULL);
    return 0;
}
