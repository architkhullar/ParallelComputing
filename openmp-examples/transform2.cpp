#include <omp.h>

int main () {
  int n = 10000;
  int* arr =new int[n] ;

#pragma omp parallel
  {
    //all threads execute before
    
#pragma omp for
    for (int i=0; i<n; ++i)
      arr[i] = 0; //workshared
    
    //all threads execute after
  }
  return 0;
}
