#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mut1, mut2;

void* f1(void* p) {
  int* val = (int*) p;
  
  for (int i=0; i< 100000; ++i) {
    pthread_mutex_lock (&mut1);
    pthread_mutex_lock (&mut2);
    *val += 1;
    pthread_mutex_unlock (&mut2);
    pthread_mutex_unlock (&mut1);
  }
  
  return NULL;
}

void* f2(void* p) {
  int* val = (int*) p;

  for (int i=0; i< 100000; ++i) {
    pthread_mutex_lock (&mut2);
    pthread_mutex_lock (&mut1);
    *val += 1;
    pthread_mutex_unlock (&mut1);
    pthread_mutex_unlock (&mut2);
  }
  
  return NULL;
}


int main () {
  pthread_t th[2];
  int val = 0;  
  pthread_mutex_init (&mut1, NULL);
  pthread_mutex_init (&mut2, NULL);
  
  pthread_create(&th[0], NULL, f1, &val);
  pthread_create(&th[1], NULL, f2, &val);

  for (int i=0; i < 2; ++i)
    pthread_join(th[i], NULL);

  printf ("%d\n", val); 

  pthread_mutex_destroy (&mut1);
  pthread_mutex_destroy (&mut2);

  
  return 0;
}
