#include <stdio.h>
#include <pthread.h>

void* f(void* p) {
  int* val = (int*) p;
  for (int i=0; i< 100000; ++i)
    *val += 1;
  return NULL;
}

int main () {
  pthread_t th[50];
  int val = 0;  
  
  for (int i=0; i < 50; ++i)
    pthread_create(&th[i], NULL, f, &val);
  for (int i=0; i < 50; ++i)
    pthread_join(th[i], NULL);

  //this usually does not print 5 000 000
  printf ("%d\n", val); 
  
  return 0;
}
