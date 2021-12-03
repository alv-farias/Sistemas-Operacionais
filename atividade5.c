#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
 
int x = 0, y = 0; // Variáveis compartilhadas
 
void funcao1(void* threadarg) {
  // Simula uma quantidade arbritária de procedimentos:
  // O trecho abaixo suspende o processo/thread por um tempo aleatório
  // Durações de suspensão possíveis 0.1, 0.2, 0.3, 0.4 ou 0,5 segundos
  srand(time(NULL)); 
  useconds_t sleepTime;
  sleepTime = (useconds_t)(((rand() % 5) + 1) * 10000); 
  usleep(sleepTime);
  // Fim da simulação
 
  // LINHA A
  x = 1;
  // LINHA B
  if (y == 0)
    printf("1 \n");
  // LINHA C
  pthread_exit(0);
}
 
void funcao2(void* threadarg) {
  // Simula uma quantidade arbritária de procedimentos:
  // O trecho abaixo suspende o processo/thread por um tempo aleatório
  // Durações de suspensão possíveis 0.1, 0.2, 0.3, 0.4 ou 0,5 segundos
  srand(time(NULL)); 
  useconds_t sleepTime;
  sleepTime = (useconds_t)(((rand() % 5) + 1) * 10000); 
  usleep(sleepTime);
  // Fim da simulação
  
  // LINHA D
  y = 1;
  // LINHA E
  if (x == 0)
    printf("2 \n");
  // LINHA F
  pthread_exit(0);
}
 
void main() {
  pthread_t t1, t2;
  // Cria e dispara t1 que executa funcao1
  pthread_create(&t1, NULL, (void*)funcao1, NULL);
  // Cria e dispara t2 que executa funcao2
  pthread_create(&t2, NULL, (void*)funcao2, NULL);
  // Pai espera filho terminar
  pthread_join(t1, NULL);
  // Pai espera filho terminar
  pthread_join(t2, NULL);
}
