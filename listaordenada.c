#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "lista.h"
int main(){
    REG reg;
    lista pi;
    reg.chave = 'c';
    initializeLista(&pi);
    for(int j=0;j<10;j++){
        reg.chave = 'a'+j;
        insertLista(&pi,reg);
    }

    printf("-- %d\n",listComparisson(last(&pi),first(&pi)));


    printf("\n\n");

      //ite dois = last(&pi);

    sortlist(pi);

    printaLista(&pi);

    return 0;
}
