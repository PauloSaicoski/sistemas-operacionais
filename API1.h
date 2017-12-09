#include <stdbool.h>

typedef struct {
  void * inicio;
  void * proxInf;
  void * proxLivre;
  int tam;
  int ocupado;
  int livre;
} buffer;

// Inicializa um buffer com capacidade para ``cap`` bytes.
// Deve ser possível usar-se quantos buffers se quiser.
// Retorna ``true`` caso a inicialização seja bem sucedida,
// ``false`` em caso contrário (``cap`` inválido ou falta de memória).
bool buffer_inicializa(buffer *b, int cap);

// Finaliza um buffer previamente inicializado.
// Todos os dados eventualmente em seu interior são perdidos.
// A memória alocada na inicialização deve ser liberada.
// Após esta chamada, o buffer não pode mais ser utilizado.
void buffer_finaliza(buffer *buf);

// insere em ``buf`` o dado apontado por ``p``, contendo ``tam`` bytes.
// ``tam`` pode ser 0, mas não pode ser negativo.
// retorna ``false`` (e não altera o estado do buffer) caso o buffer não
// tenha espaço suficiente para armazenar esse dado.
// retorna ``true`` caso o dado tenha sido inserido no buffer.
bool buffer_insere(buffer *buf, void *p, int tam);

// retorna o tamanho do maior dado que pode ser inserido no buffer
// (considerando o espaço livre no buffer e o necessário para colocar
// o tamanho do dado no buffer). O retorno deve ser negativo caso não seja
// possível inserir nem mesmo um dado de tamanho 0.
int buffer_insere_tam(buffer *buf);

// remove o próximo dado de ``buf``, colocando-o na região apontada por ``p``,
// que tem capacidade para ``cap`` bytes. Caso o próximo dado seja maior
// que ``cap``, os dados são truncados, e o que não couber em ``p`` é
// perdido. Coloca em ``*tam`` o tamanho original do dado retirado (que pode ser
// menor, igual ou maior que ``cap``).
// Retorna ``true`` se for bem sucedido, e ``false`` caso contrário
// (buffer vazio)
bool buffer_remove(buffer *buf, void *p, int cap, int *tam);

// remove o próximo dado de ``buf``, colocando-o em uma região de memória
// alocada internamente com o tamanho exato para conter esse dado.
// altera o ponteiro apontado por ``p`` para conter o endereço dessa região.
// a responsabilidade por liberar a memória alocada é de quem chama esta função.
// Coloca em ``*tam`` o tamanho do dado retirado (que é o tamanho da 
// região alocada).
// Retorna ``true`` se for bem sucedido e ``false`` caso contrário (buffer vazio)
bool buffer_remove_malloc(buffer *buf, void **p, int *tam);

// retorna o tamanho do próximo dado a ser retirado do buffer, ou -1 caso o buffer esteja vazio.
int buffer_remove_tam(buffer *buf);