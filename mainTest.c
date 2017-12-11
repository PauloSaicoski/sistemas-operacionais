
#define _GNU_SOURCE
#include "API1.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void print_timespec(struct timespec diff, const char *name){
	printf("%s.tv_sec=%ld  %s.tv_nsec=%ld\n", name, diff.tv_sec, name, diff.tv_nsec);
}

int main(){

  buffer b;
  int a;
  a=3;
  int *x;
  x=&a;

  struct timespec t1, t2;

  clock_gettime(CLOCK_MONOTONIC, &t1);

  buffer_inicializa(&b,20);
  printf ("proxInfTam %d\n", buffer_remove_tam(&b));
  printf ("tamanho %d\nlivre %d\nocupado %d\n", b.tam, b.livre, b.ocupado);
  printf ("insereTam %d\n", buffer_insere_tam(&b));
  buffer_insere(&b, (void*)x, sizeof(int));
  printf ("proxInfTam %d\n", buffer_remove_tam(&b));
  printf ("tamanho %d\nlivre %d\nocupado %d\n", b.tam, b.livre, b.ocupado);
  printf ("insereTam %d\n", buffer_insere_tam(&b));
  buffer_insere(&b, (void*)x, sizeof(int));


  printf ("proxInfTam %d\n", buffer_remove_tam(&b));
  printf ("tamanho %d\nlivre %d\nocupado %d\n", b.tam, b.livre, b.ocupado);
  printf ("insereTam %d\n", buffer_insere_tam(&b));
  buffer_finaliza(&b);
  printf ("finalizado\ntamanho %d\nlivre %d\nocupado %d\n", b.tam, b.livre, b.ocupado);
  printf ("insereTam %d\n", buffer_insere_tam(&b));
  printf ("proxInfTam %d\n", buffer_remove_tam(&b));


  printf("\n\n -------------TEMPO--------------\n\n");

  clock_gettime(CLOCK_MONOTONIC, &t2);

  print_timespec(t1, "t1");
  print_timespec(t2, "t2");

  struct timespec diff;

  if(t2.tv_nsec < t1.tv_nsec){
    diff.tv_sec  = t2.tv_sec  - t1.tv_sec  - 1;
    diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
  }
  else{
    diff.tv_sec = t2.tv_sec - t1.tv_sec;
    diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
  }

  double tempoexecucao = diff.tv_sec + (double)diff.tv_nsec/1000000000L;
  printf("Tempo decorrido   (float): %.15f segundos\n", diff.tv_sec + (double) diff.tv_nsec / 1000000000L);
  printf("Tempo decorrido (inteiro): %5ld segundos + %12ld nanosegundos\n", diff.tv_sec, diff.tv_nsec);
  printf("                  Note: %5ld segundos   eh  %12ld nanosegundos\n", 1L, 1000000000L);
  printf("\n ---------Tempo em segundos----------\n");
  printf("\n Tempo exec: %.15f seconds", tempoexecucao);
}
