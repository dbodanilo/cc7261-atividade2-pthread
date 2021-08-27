#ifndef array_h
#define array_h

#include <stdbool.h>
#include <stdio.h>

typedef struct {
  int capacity;
  int size;
  int *values;
} IntArray;

bool intArrayFromFile(IntArray *array, FILE *file);

void printIntArray(IntArray const* array);

IntArray sampleIntArray(IntArray const* array, int offset, int n);

#endif

