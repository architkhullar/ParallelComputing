#include <omp.h>

int main () {
  int n = 10000;
  int* arr = new int[n];

#pragma omp parallel for
  for (int i=0; i<n; ++i)
    arr[i] = 0;
  
  return 0;
}
