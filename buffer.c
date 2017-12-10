#include "API1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Inicializa um buffer com capacidade para ``cap`` bytes.
// Deve ser possível usar-se quantos buffers se quiser.
// Retorna ``true`` caso a inicialização seja bem sucedida,
// ``false`` em caso contrário (``cap`` inválido ou falta de memória).
bool buffer_inicializa(buffer *b, int cap)
{
  if (cap <= 0)
    return false;

  b->inicio = (void*)malloc(cap);

  if (b->inicio == NULL)
    return false;

  b->tam = cap;
  b->livre = cap;
  b->ocupado = 0;
  b->proxInf = b->inicio;
  b->proxLivre = b->inicio;
  return true;
}

// Finaliza um buffer previamente inicializado.
// Todos os dados eventualmente em seu interior são perdidos.
// A memória alocada na inicialização deve ser liberada.
// Após esta chamada, o buffer não pode mais ser utilizado.
void buffer_finaliza(buffer *buf)
{
  free(buf->inicio);
  buf->inicio = NULL;
  buf->proxInf = NULL;
  buf->proxLivre = NULL;
  buf->tam = -1;
  buf->ocupado = -1;
  buf->livre = -1;
}

int buffRest(buffer * buf, int i){ //calcula quanto falta para que seja necessario dar a volta no buffer, i = 1 para proxLivre e i = 2 para proxInf
  if (i == 1){
    return (buf->inicio + buf->tam) - buf->proxLivre;
  }
  if (i == 2){
    return (buf->inicio + buf->tam) - (void*)buf->proxInf;
  }
}

void copiaProBuf(buffer * buf, void * info, int tam){ //copia informações para dentro do buffer circular e avança a variavel buf->proxLivre
  int bufRest;
  bufRest = buffRest(buf, 1);
  if (bufRest<tam){
    memcpy(buf->proxLivre, info, bufRest);
    info +=bufRest;
    buf->proxLivre = buf->inicio;
    memcpy(buf->proxLivre, info, tam-bufRest);
    buf->proxLivre += (tam-bufRest);
  }
  else{
    memcpy(buf->proxLivre, info, tam);
    buf->proxLivre += tam;
  }
}

// insere em ``buf`` o dado apontado por ``p``, contendo ``tam`` bytes.
// ``tam`` pode ser 0, mas não pode ser negativo.
// retorna ``false`` (e não altera o estado do buffer) caso o buffer não
// tenha espaço suficiente para armazenar esse dado.
// retorna ``true`` caso o dado tenha sido inserido no buffer.
bool buffer_insere(buffer *buf, void *p, int tam)
{
  if (tam > buffer_insere_tam(buf) || tam < 0)
  {
    return false;
  }
  copiaProBuf(buf, &tam, sizeof(int));
  copiaProBuf(buf, p, tam);
  buf->livre -= (tam + sizeof(int));
  buf->ocupado += (tam + sizeof(int));
  return true;
}

// retorna o tamanho do maior dado que pode ser inserido no buffer
// (considerando o espaço livre no buffer e o necessário para colocar
// o tamanho do dado no buffer). O retorno deve ser negativo caso não seja
// possível inserir nem mesmo um dado de tamanho 0.
int buffer_insere_tam(buffer *buf){
  int insereTam;
  insereTam = buf->livre - sizeof(int);
  if (insereTam < 0)
    return -1;
  else
    return insereTam;
}

void avancaProxInf(buffer * buf, int qnt){
  int bufRest;
  bufRest = buffRest(buf, 2);
  if (bufRest <= qnt){
    buf->proxInf = buf->inicio+(qnt-bufRest);
  }
  else{
    buf->proxInf += qnt;
  }
}

void copiaDoBufAux(void * p, buffer * b, int tam){
  memcpy(p, b->proxInf, tam);
  avancaProxInf(b,tam);
}

void copiaDoBuf(void * p, buffer * b, int tam){
  avancaProxInf(b, sizeof(int));
  int bufRest;
  bufRest = buffRest(b, 2);
  if(bufRest<tam){
    copiaDoBufAux(p, b, bufRest);
    copiaDoBufAux(p, b, tam-bufRest);
  }
  else{
    copiaDoBufAux(p, b, tam);
  }
}

// remove o próximo dado de ``buf``, colocando-o na região apontada por ``p``,
// que tem capacidade para ``cap`` bytes. Caso o próximo dado seja maior
// que ``cap``, os dados são truncados, e o que não couber em ``p`` é
// perdido. Coloca em ``*tam`` o tamanho original do dado retirado (que pode ser
// menor, igual ou maior que ``cap``).
// Retorna ``true`` se for bem sucedido, e ``false`` caso contrário
// (buffer vazio)
bool buffer_remove(buffer *buf, void *p, int cap, int *tam){
  if (buffer_remove_tam(buf) < 0){
    return false;
  }
  *tam = buffer_remove_tam(buf);
  if(cap < *tam){
    copiaDoBuf(p, buf, cap);
    avancaProxInf(buf, *tam-cap);
  }
  else{
    copiaDoBuf(p, buf, *tam);
  }
  
  buf->livre += *tam+sizeof(int);
  buf->ocupado -= *tam+sizeof(int);
  return true;
}

// remove o próximo dado de ``buf``, colocando-o em uma região de memória
// alocada internamente com o tamanho exato para conter esse dado.
// altera o ponteiro apontado por ``p`` para conter o endereço dessa região.
// a responsabilidade por liberar a memória alocada é de quem chama esta função.
// Coloca em ``*tam`` o tamanho do dado retirado (que é o tamanho da
// região alocada).
// Retorna ``true`` se for bem sucedido e ``false`` caso contrário (buffer vazio)
bool buffer_remove_malloc(buffer *buf, void **p, int *tam){
  if (buffer_remove_tam(buf) < 0){
    return false;
  }
  *tam = buffer_remove_tam(buf);
  void * aux;
  aux = malloc (*tam*sizeof(int));
  copiaDoBuf(aux,buf,*tam);
  *p = aux;
  buf->livre += *tam+sizeof(int);
  buf->ocupado -= *tam+sizeof(int);
  return true;
}

// retorna o tamanho do próximo dado a ser retirado do buffer, ou -1 caso o buffer esteja vazio.
int buffer_remove_tam(buffer *buf){
  if (buf->ocupado <=0){
    return -1;
  }
  int bufRest = buffRest(buf, 2);
  int aux2;
  void* aux;
  aux = &aux2;
  if (sizeof(int) > bufRest ){
    memcpy(aux, buf->proxInf, bufRest);
    memcpy((aux+bufRest), buf->inicio, sizeof(int)-bufRest);
  }
  else {
    memcpy(aux, buf->proxInf, sizeof(int));
  }
  return aux2;
}
