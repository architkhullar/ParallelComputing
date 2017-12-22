#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mut;
pthread_cond_t cond;
bool score, ping;
  
void* f1(void* p) {
  unsigned int seed = 1;
  
  pthread_mutex_lock (&mut);
  while (!score) {

    while (!ping) {
      pthread_cond_wait(&cond, &mut);
    }
    
    if (!score){
      printf("ping\n");
      ping = !ping;

      if (rand_r(&seed) % 17 == 0) {
	printf ("score 1\n");
	score = true;
      }
      
      pthread_cond_signal (&cond);
    } 
  }
  pthread_mutex_unlock (&mut);
  return NULL;
}

void* f2(void* p) {
  unsigned int seed = 2;
  
  pthread_mutex_lock (&mut);
  while (!score) {
    while (ping) {
      pthread_cond_wait(&cond, &mut);
    }
    
    if (!score){
      printf("pong\n");
      ping = !ping;

      if (rand_r(&seed) % 17 == 0) {
	printf ("score 2\n");
	score = true;
      }
      
      pthread_cond_signal (&cond);
    } 
  }
  pthread_mutex_unlock (&mut);
  return NULL;
}


int main () {
  score = false;
  ping = true;
  pthread_t th[2];
  
  pthread_mutex_init (&mut, NULL);
  pthread_cond_init(&cond, NULL);

  pthread_create(&th[0], NULL, f1, NULL);
  pthread_create(&th[1], NULL, f2, NULL);

  for (int i=0; i < 2; ++i)
    pthread_join(th[i], NULL);

  pthread_cond_destroy (&cond);
  pthread_mutex_destroy (&mut);
  
  
  return 0;
}
