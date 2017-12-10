#include "API1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
  buffer b;
  int a;
  a=3;
  int *x;
  x=&a;
  void *y;
  y=malloc(sizeof(int));
  int tam;
  buffer_inicializa(&b,18);
  buffer_insere(&b, (void*)x, sizeof(int));
  buffer_insere(&b, (void*)x, sizeof(int));
  buffer_remove(&b, y, sizeof(int), &tam);
  printf ("%d\n", *((int*)y));
  printf ("insere tam %d\n", buffer_insere_tam(&b));
  printf ("remove tam %d\n\n", buffer_remove_tam(&b));
  buffer_insere(&b, (void*)x, sizeof(int));
  printf ("insere tam %d\n", buffer_insere_tam(&b));
  printf ("remove tam %d\n\n", buffer_remove_tam(&b));
  buffer_remove(&b, y, sizeof(int), &tam);
  printf ("%d\n", *((int*)y));
  printf ("insere tam %d\n", buffer_insere_tam(&b));
  printf ("remove tam %d\n\n", buffer_remove_tam(&b));
  buffer_insere(&b, (void*)x, sizeof(int));
  printf ("insere tam %d\n", buffer_insere_tam(&b));
  printf ("remove tam %d\n\n", buffer_remove_tam(&b));
  buffer_remove(&b, y, sizeof(int), &tam);
  printf ("%d\n", *((int*)y));
  printf ("insere tam %d\n", buffer_insere_tam(&b));
  printf ("remove tam %d\n\n", buffer_remove_tam(&b));
  buffer_insere(&b, (void*)x, sizeof(int));
  printf ("insere tam %d\n", buffer_insere_tam(&b));
  printf ("remove tam %d\n\n", buffer_remove_tam(&b));
  buffer_remove(&b, y, sizeof(int), &tam);
  printf ("%d\n", *((int*)y));
  printf ("insere tam %d\n", buffer_insere_tam(&b));
  printf ("remove tam %d\n\n", buffer_remove_tam(&b));
  buffer_remove(&b, y, sizeof(int), &tam);
  printf ("%d\n", *((int*)y));
  printf ("insere tam %d\n", buffer_insere_tam(&b));
  printf ("remove tam %d\n\n", buffer_remove_tam(&b));
  buffer_insere(&b, (void*)x, sizeof(int));
  printf ("insere tam %d\n", buffer_insere_tam(&b));
  printf ("remove tam %d\n\n", buffer_remove_tam(&b));
  buffer_remove(&b, y, sizeof(int), &tam);
  printf ("%d\n", *((int*)y));
  printf ("insere tam %d\n", buffer_insere_tam(&b));
  printf ("remove tam %d\n\n", buffer_remove_tam(&b));
  buffer_remove(&b, y, sizeof(int), &tam);
  printf ("%d\n", *((int*)y));
  printf ("insere tam %d\n", buffer_insere_tam(&b));
  printf ("remove tam %d\n\n", buffer_remove_tam(&b));
  buffer_remove(&b, y, sizeof(int), &tam);
  printf ("%d\n", *((int*)y));
  printf ("insere tam %d\n", buffer_insere_tam(&b));
  printf ("remove tam %d\n\n", buffer_remove_tam(&b));
  buffer_remove(&b, y, sizeof(int), &tam);
  printf ("%d\n", *((int*)y));
  printf ("insere tam %d\n", buffer_insere_tam(&b));
  printf ("remove tam %d\n\n", buffer_remove_tam(&b));
  buffer_insere(&b, (void*)x, sizeof(int));
  printf ("insere tam %d\n", buffer_insere_tam(&b));
  printf ("remove tam %d\n\n", buffer_remove_tam(&b));
  buffer_insere(&b, (void*)x, sizeof(int));
  printf ("insere tam %d\n", buffer_insere_tam(&b));
  printf ("remove tam %d\n\n", buffer_remove_tam(&b));
  buffer_insere(&b, (void*)x, sizeof(int));
  printf ("insere tam %d\n", buffer_insere_tam(&b));
  printf ("remove tam %d\n\n", buffer_remove_tam(&b));



  free(y);
  buffer_finaliza(&b);
  return 0;
}
