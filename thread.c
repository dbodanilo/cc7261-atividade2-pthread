#include <assert.h>
#include <pthread.h>
#include <stdlib.h>

#include "array.h"
#include "serial.h"

void *serial_pthread(void *args) {
  assert(args != NULL);

  IntArray *array = (IntArray *)args;
  int *nprimos = malloc(sizeof(int));

  *nprimos = resolve_serial(array);

  free(args);  

  pthread_exit((void *)nprimos);

  return NULL;
}

int resolve_thread(IntArray const* array, int nthreads) {
  int nprimos = 0;
  pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t)*nthreads);
 
  int size_thread = array->size / nthreads;

  for (int i = 0; i < nthreads; i += 1) {

    int nprevious = i * size_thread;

    if (i == nthreads - 1) size_thread = array->size - nprevious;

    IntArray *array_thread = malloc(sizeof(IntArray));
    *array_thread = sampleIntArray(array, nprevious, size_thread);    
    int r = pthread_create(threads + i, NULL, serial_pthread, (void *) array_thread);
    assert(r == 0);
  }

  for (int i = 0; i < nthreads; i += 1) {
    int *nprimos_thread;
    pthread_join(threads[i], (void **)&nprimos_thread);

    nprimos += *nprimos_thread;

    free(nprimos_thread);
  }
  
  free(threads);

  return nprimos;
}

