#include "iterador.h"

#include <stdio.h>
#include <stdlib.h>

ite first(lista* l ){
    ite i;
    i.posicao = l->head->next;
    i.estrutura = l;
    return i;
}
ite last(lista* l ){
    ite i;
    i.posicao = l->head->prev;
    i.estrutura = l;
    return i;
}
char elemento(ite l){
    return l.posicao->reg.chave;
}

ite next(ite l){
    if(!acabou(l)){
        l.posicao = l.posicao->next;
        return l;
    }//oq fazer se estiver no ultimo ?

}

int acabou( ite i ) {
    return i.posicao->next == i.estrutura->head;
}
//para adicionar no meio, tem duas opções, dps de certo item, ou antes
// se foi dps do el2 ficaria =   <-head -> (<-el1) -> (<-el2) -> (<-el3)
// <-head -> (<-el1) -> (<-el2) ->(<-el4)-> (<-el3)

void insertMiddleLista(lista *l,REG reg, ite i){
    POINTER new = (POINTER)malloc(sizeof(ELEM));
    new->reg = reg;
    int tam = sizeLista(l);

    new->next = i.posicao->next;
    i.posicao->next->prev = new;//caso especial, um item na lista.
    i.posicao->next = new;
    new->prev = i.posicao;

    l->qtd++;
}
int removeItemMiddleLista(lista *l, REG reg, ite i){
    if(acabou(i)){
        return -1;//so nao posso remover a head/sentinela.
    }
    POINTER remove = (POINTER)malloc(sizeof(ELEM));


}

