#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "lista.h"
int main(){

    lista pi;
    char reg = 'c';
    initializeLista(&pi);
    for(int j=0;j<8;j++){
        reg = 'f'+j;
        insertLista(&pi,reg);
    }
    printf("\n\n");

      //ite dois = last(&pi);

    sortlist(pi);

    printaLista(&pi);

    return 0;
}
