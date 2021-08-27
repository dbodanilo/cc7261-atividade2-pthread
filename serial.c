#include <stdbool.h>
#include <math.h>

#include "array.h"

bool isprime(int n) {
  for (int i = 2; i <= sqrt(n); i += 1) {
    if (n % i == 0) return false;
  }

  return true;
}

int resolve_serial(IntArray const* array) {
  int nprimos = 0;

  for (int i = 0; i < array->size; i += 1) {
    if (isprime(array->values[i])) nprimos += 1;
  }

  return nprimos;
}

