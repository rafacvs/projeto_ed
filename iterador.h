#ifndef ITERADOR_H
#define ITERADOR_H

#include "lista.h"
/*
Gabriel Bellon de Carvalho - 802430
Ivan Capeli Navas - 802286
Rafael de Campos Villa da Silveira - 801968
*/


typedef struct{
    POINTER posicao;
    lista* estrutura;
}ite;

ite first(lista* l );
ite last(lista* l);
ite next(ite l);
int acabou( ite i );
char elemento(ite l);
#endif

