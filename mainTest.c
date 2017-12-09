#include "API1.h"
#include <stdio.h>

int main(){
  buffer b;
  int a;
  a=3;
  int *x;
  x=&a;
  buffer_inicializa(&b,10);
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
}
