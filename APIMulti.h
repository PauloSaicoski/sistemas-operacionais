#include <stdbool.h>
#include <pthread.h>
#include "API1.h"

typedef struct {
  pthread_mutex_t escrita;
  pthread_mutex_t escritaTam;
  pthread_mutex_t leitura;
  pthread_mutex_t leituraTam;
  buffer buff;
} bufc;

// Inicializa um buffer com capacidade para ``cap`` bytes.
// Deve ser possível usar-se quantos buffers se quiser.
// Retorna ``true`` caso a inicialização seja bem sucedida,
// ``false`` em caso contrário (``cap`` inválido ou falta de memória).
// Esta função só deve ser chamada uma vez para um buffer, e deve ser a 
// primeira função chamada para esse buffer.
bool bufc_inicializa(bufc *b, int cap);

// Finaliza um buffer previamente inicializado.
// Todos os dados eventualmente em seu interior são perdidos.
// A memória alocada na inicialização deve ser liberada.
// Essa função deve ser chamada uma única vez para um buffer.
// Após esta chamada, o buffer não pode mais ser utilizado.
void bufc_finaliza(bufc *b);

// insere em ``b`` o dado apontado por ``p``, contendo ``tam`` bytes.
// ``tam`` pode ser 0, mas não pode ser negativo.
// retorna ``false`` (e não altera o estado do buffer) caso o buffer não
// tenha capacidade suficiente para armazenar esse dado ou se o buffer já tiver
// sido finalizado.
// caso o buffer não tenha espaço suficiente para a inserção, ou já tenha alguma
// thread bloqueada em inserção neste mesmo buffer, bloqueia a thread realizando
// esta chamada.
// retorna ``true`` quando o dado for inserido no buffer.
bool bufc_insere(bufc *b, void *p, int tam);

// remove o próximo dado de ``b``, colocando-o na região apontada por ``p``,
// que tem capacidade para ``cap`` bytes. Caso o próximo dado seja maior
// que ``cap``, os dados são truncados, e o que não couber em ``p`` é
// perdido. Coloca em ``*tam`` o tamanho original do dado retirado (que pode ser
// menor, igual ou maior que ``cap``).
// Retorna ``false`` se o buffer tiver sido finalizado.
// Bloqueia a thread chamadora enquanto o buffer estiver vazio.
// Retorna ``true`` quando for bem sucedido.
bool bufc_remove(bufc *b, void *p, int cap, int *tam);

// remove o próximo dado de ``b``, colocando-o em uma região de memória
// alocada internamente com o tamanho exato para conter esse dado.
// altera o ponteiro apontado por ``p`` para conter o endereço dessa região.
// a responsabilidade por liberar a memória alocada é de quem chama esta função.
// Coloca em ``*tam`` o tamanho do dado retirado (que é o tamanho da 
// região alocada).
// Retorna ``false`` se o buffer tiver sido finalizado.
// Bloqueia a thread chamadora enquanto o buffer estiver vazio.
// Retorna ``true`` quando for bem sucedido.
bool bufc_remove_malloc(bufc *b, void **p, int *tam);