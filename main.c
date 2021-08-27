#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "array.h"
#include "serial.h"
#include "thread.h"

//int main(int argc, char *argv[]) {
int main(void) {
  // open file 
  char datafilename[] = "data2.csv";
  FILE *datafile = fopen(datafilename, "r");

  IntArray data = { 1, 0, (int*)malloc(sizeof(int)) };
  intArrayFromFile(&data, datafile); 
 
  fclose(datafile);

  printf("Analise de %d valores\n", data.size);

  int n = 50; // número de repetições
  printf("%d repeticoes\n", n);

  double sum_tserial = 0;
  int nprimos_serial = 0;
  for (int i = 0; i < n; i += 1) {
    struct timeval start, end;

    // Timestamp start
    gettimeofday(&start, NULL);

    // execução serial
    nprimos_serial = resolve_serial(&data);

    // Timestamp end
    gettimeofday(&end, NULL);

    long tserial = (end.tv_sec - start.tv_sec) * 1000000l + (end.tv_usec - start.tv_usec);
    sum_tserial += tserial;
  }
  double avg_tserial = sum_tserial / n; 
  
  printf("---\n");
  printf("execucao serial\n");
  printf("%.2lf ms\n", avg_tserial/1000.0);
  printf("%d numeros primos encontrados\n", nprimos_serial);
  printf("---\n");

  for (int i = 2; i < 260; i *= i) {
    double sum_tthread = 0;
    int nprimos_thread = 0;

    for (int j = 0; j < n; j += 1) {
      struct timeval start, end;

      // Timestamp start
      gettimeofday(&start, NULL);

      // execução paralela
      nprimos_thread = resolve_thread(&data, i);

      // Timestamp end
      gettimeofday(&end, NULL);

      long tthread = (end.tv_sec - start.tv_sec) * 1000000l + (end.tv_usec - start.tv_usec);
      sum_tthread += tthread;
    }
    
    double avg_tthread = sum_tthread / n;

    printf("---\n");
    printf("%d threads\n", i);
    printf("%.2lf ms\n", avg_tthread/1000.0);
    printf("%d numeros primos encontrados\n", nprimos_thread);
    printf("SpeedUp = %.4lf\n", avg_tserial / avg_tthread);
    printf("---\n");
  }

  free(data.values);

  return 0;
}

