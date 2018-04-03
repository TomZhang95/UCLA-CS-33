//
//  main.c
//  treethread
//
//  Created by Tom Zhang on 5/31/17.
//  Copyright © 2017 Tom Zhang. All rights reserved.
//

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

void* thread(void* vargp);

struct s {
  int n;
  int t;
  sem_t *lock;
}vars;

int main(int argc, const char * argv[]) {
  int nthreads = atoi(argv[1]);
  int temp = 1;
  sem_t semlock;
  sem_init(&semlock, 0, 1);
  if (nthreads < 1)
    return 0;
  for (int i = 0; i < nthreads; i++) {
    temp *= 2;
  }
  vars.t = temp - 2;
  vars.n = vars.t - 1;
  vars.lock = &semlock;
  pthread_t tid;
  pthread_create(&tid, NULL, thread, &vars);
  pthread_join(tid, NULL);
  return 0;
}

void* thread(void* vargp) {
  struct s* t_vars;
  t_vars = (struct s*)vargp;

  sem_wait(t_vars->lock);
  if (t_vars->n == 0) {
    if (t_vars->n == -1)
      return NULL;
    printf("Thread ");
    printf("%d", t_vars->t);
    printf(" done\n");
    t_vars->n = -1;
    sem_post(t_vars->lock);
    return NULL;
  }
  sem_post(t_vars->lock);
  if (t_vars->n > 0){
    pthread_t tid;
    pthread_create(&tid, NULL, thread, t_vars);
    t_vars->n -= 1;
    if (t_vars->n == 0) {
      pthread_join(tid, NULL);
      return NULL;
    }
    pthread_t tid2;
    pthread_create(&tid2, NULL, thread, t_vars);
    t_vars->n -= 1;
    pthread_join(tid, NULL);
    pthread_join(tid2, NULL);
    return NULL;
  }
}
