/*
Gabriel Bellon de Carvalho - 802430
Ivan Capeli Navas - 802286
Rafael de Campos Villa da Silveira - 801968
*/

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>

#include "lista.h"
#include "pilha.h"

typedef struct {
  lista mao;
  int soma;
  int fichas;
  int aposta_atual;
  int gameover;  // Perdeu o round, e logo as fichas da aposta atual.
  int quit;      // Saiu do jogo.
} PERSON;

int getValue(char card, int aceValue);                                                  // Retorna o valor de cada carta passada.
void swap(int v[], int a, int b);                                                       // Troca os itens do indice em 'a' e 'b' do vetor v[].
void shuffle(int vetor[], int n);                                                       // Embaralha o baralho.
void comprarCarta(pilha *p, PERSON *jogador, int mesa);                                 // Funcao para comprar carta, retirar da pilha e adicionar na lista de cada jogador.
void jogadaMesa(PERSON jogadores[], int qtdJogadores, pilha *p);                        // Funcao para emular a mesa, um jogador que joga pro cassino.
void initializePlayers(int qtdJogadores, PERSON jogadores[qtdJogadores], int isFirst);  // Inicializa os jogadores seguindo as regras do jogo, ou se ja estiver inicializado apenas limpa a mao de cada jogador.
void firstRound(pilha p, int qtdJogadores, PERSON jogadores[qtdJogadores]);             // Primeira rodada do jogo.
void rounds(pilha p, int qtdJogadores, PERSON jogadores[qtdJogadores]);                 // Rodadas seguintes.
void summary(int qtdJogadores, PERSON jogadores[qtdJogadores], PERSON mesa);            // Tela que mostra o resultado de cada jogador, se ganhou, perdeu ou empatou.
void printRules();                                                                      // Mostra as regras para os jogadores.
void prosseguir();                                                                      // Segue o jogo, e limpa o console.
void saidajogadores(int qtdJogadores, PERSON jogadores[qtdJogadores]);                  // Momento em que os jogadores sem fichas sao eliminados automaticamente, e o jogo da a opcao de sair ou continuar pra quem tem ficha.

#endif
