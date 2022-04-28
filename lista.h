/*
Gabriel Bellon de Carvalho - 802430
Ivan Capeli Navas - 802286
Rafael de Campos Villa da Silveira - 801968
*/

#ifndef LISTA_H
#define LISTA_H

typedef struct aux {
  char reg;
  struct aux *prev;
  struct aux *next;
} ELEM;

typedef ELEM *POINTER;

typedef struct {
  POINTER head;
  unsigned qtd;
} lista;

typedef struct{
    POINTER posicao;
    lista* estrutura;
}ite;

void initializeLista(lista *l); // Aloca memoria para lista, inicializando-a.
void insertLista(lista *l, char reg); // Insere elemento no comeco.
void insertEndLista(lista *l, char reg); // Insere elemento no final.
int removeItemLista(lista *l); // Remove o elemento depois da sentinela, isso eh, remove o primeiro elemento da estrutura.
int removeItemEndLista(lista *l); // Remove o elemento antes da sentinela, ou seja, o ultimo elemento.
int sizeLista(lista *l); // Retorna o tamanho da lista.
void printaLista(lista *l); // Printa todos os elementos da lista.
void destroiLista(lista *l); // Desaloca completamente a lista.
void clearLista(lista *l); // Remove todos elementos da lista, porem a estrutura continua alocada.

void swapi(ite one, ite two); // Faz a troca entre de registros entre os iteradores passados na função.
ite first(lista* l ); // Inicializaa um iterador para o primeiro elemento da lista.
ite last(lista* l); // Inicializaa um iterador para o ultimo elemento da lista.
ite next(ite l); // Itera pela lista.

int acabou( ite i ); // Retorna 1 se estaa no final da lista.

char elemento(ite l); // Retorna o registro(char) do elemento.
char removeItemMiddleLista(lista *l, ite i);

void insertMiddleLista(lista *l,char reg, ite i);
void sortlist(lista pi,int (*listComparisson)(ite um,ite dois)); // Faz o sort da lista de modo quadratico, o segundo argumento eh uma funcao de ordenacao.
// para funcionar corretamente o retorno dessa funcao deve ser 1 quando o usuario desejar que uma troca seja feita, 0 caso ao contrario.

#endif
