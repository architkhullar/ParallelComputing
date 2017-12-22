#include <stdio.h>
#include <pthread.h>

void* f(void* p) {
  printf ("%s\n", p);
  return NULL;
}

int main () {
  pthread_t teach, student[5];
  char pm[] = "Hello, my name is Erik.";
  char sm[] = "Hello Erik!";
  
  pthread_create(&teach, NULL, f, pm); //create a new thread
  pthread_join (teach, NULL); //wait for completion
  
  //create 50 threads
  for (int i=0; i < 5; ++i)
    pthread_create(&student[i], NULL, f, sm);

  //wait for the 50 threads to complete
  for (int i=0; i < 5; ++i)
    pthread_join(student[i], NULL);
  return 0;
}
