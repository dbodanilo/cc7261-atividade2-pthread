#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "array.h"

// store file contents in an array
bool intArrayFromFile(IntArray *array, FILE *file) {
  if (array == NULL) return false;

  int num;
  while(fscanf(file, "%d", &num) != EOF) {
    if (array->capacity < array->size + 1) {
      array->capacity *= 2;
      array->capacity += 1; // handles capacity of 0

      array->values = (int*)realloc(array->values, sizeof(int)*(array->capacity));
      if (array->values == NULL) return false;
    }

    array->values[array->size] = num;
    array->size += 1;
  }
  
  return true;
}

void printIntArray(IntArray const* array) {
  for (int i = 0; i < array->size; i += 1) {
    printf("%d", array->values[i]);
    if (i < array->size - 1) printf(" ");
  }
}

IntArray sampleIntArray(IntArray const* array, int offset, int n) {
  IntArray sample = { array->capacity - offset, n, array->values + offset };

  return sample;
}

