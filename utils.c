#include "utils.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getValue(char card, int aceValue) {// Funcao que retorna o valor da carta no 21, foi usado o 'X' como 10 para facilitar a criacao do programa.
  //tambem eh usada a flag acevalue para checar a opcao preferida do usuario.
  switch (card) {
    case 'A':
      if (aceValue == 1) {
        return 11;
      } else {
        return 1;
      }
      break;
    case '2':
      return 2;
      break;
    case '3':
      return 3;
      break;
    case '4':
      return 4;
      break;
    case '5':
      return 5;
      break;
    case '6':
      return 6;
      break;
    case '7':
      return 7;
      break;
    case '8':
      return 8;
      break;
    case '9':
      return 9;
      break;
    case 'X':
      return 10;
      break;
    case 'J':
      return 10;
      break;
    case 'Q':
      return 10;
      break;
    case 'K':
      return 10;
      break;
  }
}

void swap(int v[], int a, int b) {//faz uma troca entre os indices a e b de um vetor v.
  int temp = v[a];
  v[a] = v[b];
  v[b] = temp;
}

void shuffle(int vetor[], int n) {//funcao que recebe um vetor e o embaralha de uma maneira "randomica"
  srand(time(NULL));

  for (int i = 0; i < n; i++) {
    int j = i + rand() % (n - i);

    swap(vetor, i, j);//troca os elementos de posicao
  }
}

void comprarCarta(pilha *p, PERSON *jogador, int mesa) {//funcao que retira uma carta do baralho(pilha) e adiciona na mao dos jogadores(lista)
  //int mesa eh uma flag pra denotar que o jogador eh ou nao a mesa(1 para sim, 0 nao)
  if (jogador->soma < 21) {//checa se a soma atual ja eh maior que 21
    // se mesa for igual a 1, quer dizer que a mesa esta comprandos cartas.

    int aceValue = -1;
    char option;

    char element = topoPilha(p);//o elemento a ser comparador eh igual ao topo da pilha(elemento a ser retirado)

    if (element == 'X') {
      printf("Carta = 10\n");//Como dito anteriormente, foi usado x no lugar do 10 para facilitar a implementação
    } else {
      printf("Carta = %c\n", element);  // mudar o acesso ao campo, com iterador.
    }

    if (element == 65) {//se for o A's

      if (mesa == 0) {//checa se quem pegou um A's foi a mesa ou outros jogadores.
        printf("A vale 11? (S ou N)\n");
        while (1) {
            scanf(" %c", &option);
            if (option != 'S' && option != 'N' && option != 's' && option != 'n')
              printf("Caractere invalido. Digite S ou N.\n");
            else
              break;
          }//recebe do jogador a opcao do A's valer 11 ou nao, como dito nas regras
        option = toupper(option);//coloca a opcao em maiusculo
      } else {
        if (jogador->soma + 11 > 21)//checa pra mesa se ela vai querer ou nao que valha 21.
          option = 'N';
        else
          option = 'S';
      }

      if (option == 'S') {//seta a flag para ser usada na funcao getvalue();
        aceValue = 1;
      } else {
        aceValue = 0;
      }
    }

    jogador->soma += getValue(element, aceValue);//adiciona  a carta comprada a soma do jogador atual.

    insertLista(&jogador->mao, element);//insere a carta na mao do jogador.

    removePilha(p);//tira a corta atual do topo da pilha.
  }
}

void jogadaMesa(PERSON jogadores[], int qtdJogadores, pilha *p) {//funcao para emular uma mesa, um jogador que tem como missao ganhar dos outros e dar dinheiro para o cassino.
  printf("MESA\n");
  printf("-----------\n");

  int num, ganhou;  // ganhou verifica de quantos jogadores a mesa ganhou.
  int players_out = 0;

  srand(time(NULL));
  num = rand() % 100;//num denotaria uma mesa que as vezes analisaria a situacao atual do jogo, ou seja, quantas pessoas estao jogando, de quantas pessoas a mesa esta perdendo,
    //ou apenas compraria a carta mesmo que talvez perca.
  for (int i = 0; i < qtdJogadores - 1; i++) {
    if (jogadores[i].gameover == 1) players_out++;
  }

  if (players_out != qtdJogadores - 1) {
    if (num <= 15) {
      printf("Mesa comprou!\n\n");
      comprarCarta(p, &jogadores[qtdJogadores - 1], 1);
      printf("Soma atual: %i\n\n", jogadores[qtdJogadores - 1].soma);
    } else if (num > 30) {
      for (int j = 0;; j++) {
        ganhou = 0;

        for (int i = 0; i < qtdJogadores - 1; i++) {
          // Se a mesa ganhar da maioria ela nao compra, se nao ela compra e checamos de novo.
          if (jogadores[qtdJogadores - 1].soma > jogadores[i].soma)
            ganhou += 1;
        }

        if (jogadores[qtdJogadores - 1].soma >= 21 || ganhou >= ((qtdJogadores - 1) / 2) + 1) {
          if (j == 0)
            printf("Mesa nao comprou!\n\n");

          break;
        } else {
          printf("Mesa comprou!\n\n");
          comprarCarta(p, &jogadores[qtdJogadores - 1], 1);
          printf("Soma atual: %i\n\n", jogadores[qtdJogadores - 1].soma);
        }
      }
    } else
      printf("Mesa nao comprou!\n\n");
  } else {
    printf("Mesa nao comprou!\n\n");
  }
}

void initializePlayers(int qtdJogadores, PERSON jogadores[qtdJogadores], int isFirst) {//iniciliaza a mao dos jogadores(lista) ou se a lista ja existir, apenas limpa as maos.
  // INITALIZE PLAYER DATA
  for (int i = 0; i < qtdJogadores; i++) {
    if (isFirst == 1) {
      initializeLista(&jogadores[i].mao);
    } else {
      clearLista(&jogadores[i].mao);
    }

    jogadores[i].soma = 0;//soma das cartas comeca em 0
    jogadores[i].gameover = 0;
    // jogadores[i].fichas = 1250;
  }
}

void firstRound(pilha p, int qtdJogadores, PERSON jogadores[qtdJogadores]) {//funcao para o primeiro round, pois eh diferente dos outros rounds.
  system("@cls||clear");//funcao para limpar o terminal e ficar mais bonito.

  printf("=========== DISTRIBUINDO CARTAS ===========\n\n");
  // ROUND INICIAL: 2 CARTAS PARA CADA JOGAODR E MESA
  for (int i = 0; i < qtdJogadores; i++) {
    if (jogadores[i].quit != 1 || i == qtdJogadores - 1) {
      if (i == qtdJogadores - 1) {//checa se o atual eh a mesa.
        printf("MESA\n");
      } else {
        printf("JOGADOR %i\n", i + 1);
      }
      printf("--------------\n");
      if (i != qtdJogadores - 1) {
        while (1) {
          printf("Fichas atuais: %i\n", jogadores[i].fichas);
          printf("Quanto quer apostar?\n");
          scanf("%i", &jogadores[i].aposta_atual);

          if (jogadores[i].aposta_atual > jogadores[i].fichas) {//caso que a aposta digitada pelo jogador seja maior com o que ele realmente tenha.
            printf("Saldo insuficiente, ");
          } else {
            break;
          }
        }

        jogadores[i].fichas -= jogadores[i].aposta_atual;//retira das fichas do jogador a aposta que ele fez.
      }

      for (int j = 0; j < 2; j++) {//compra duas cartas para cada jogador.
        if (i == qtdJogadores - 1)
          comprarCarta(&p, &jogadores[i], 1);
        else
          comprarCarta(&p, &jogadores[i], 0);
      }

      printf("Soma = %i\n\n", jogadores[i].soma);

      printf("\n");
    }
  }
}

void rounds(pilha p, int qtdJogadores, PERSON jogadores[qtdJogadores]) {//rounds normais.
  system("@cls||clear");
  printf("=========== JOGADAS INVIDUAIS ===========\n\n");
  // ROUNDS
  for (int i = 0; i < qtdJogadores - 1; i++) {
    if (jogadores[i].quit != 1) {
      int stop = 0;//flag pra quando o jogador quiser parar de comprar
      char option;

      while (stop == 0) {

        if (jogadores[i].soma > 21) {//se a soma eh maior que 21, nao da pra comprar mais cartas.
          jogadores[i].gameover = 1;
          stop = 1;
          break;
        } else if (jogadores[i].soma < 21) {//enquanto o jogador tem menos que 21.
          system("@cls||clear");

          printf("JOGADOR %i\n", i + 1);
          printf("-----------\n");

          printf("Fichas atuais: %i\n\n", jogadores[i].fichas);
          printf("Aposta: %i\n", jogadores[i].aposta_atual);
          printf("Soma atual: %i\n\n", jogadores[i].soma);

          printf("O que voce deseja?\n");
          printf("  Comprar mais ou parar? (C ou P)\n");

          //scanf(" %c", &option);
          while (1) {//pede a opcao se quer parar ou continuar comprando
            scanf(" %c", &option);
            if (option != 'C' && option != 'P' && option != 'c' && option != 'p')
              printf("  Caractere invalido. Digite C ou P.\n");
            else
              break;
          }
          option = toupper(option);

          if (option == 'C') {
            comprarCarta(&p, &jogadores[i], 0);
            printf("\n");
          } else {
            stop = 1;
            prosseguir();
          }
        } else {//caso no qual o jogador faz 21(ou seja ganhou, ou empatou)
              printf("JOGADOR %i\n", i + 1);
              printf("-----------\n");
              printf("Soma atual: %i\n", jogadores[i].soma);
              printf("Sua soma eh igual a 21, nao eh possivel comprar mais.\n\n\n");
              prosseguir();
              stop = 1;
          //printf("Ganhou! soma = 21\n");
          //stop = 1;
        }
      }
    }

    if (jogadores[i].soma > 21) {
      printf("Soma atual: %i\n", jogadores[i].soma);
      printf("Sua soma eh maior que 21, nao eh possivel comprar mais.\n\n\n");
      prosseguir();
    }
  }
}

void summary(int qtdJogadores, PERSON jogadores[qtdJogadores], PERSON mesa) {//sumario eh a finalizacao do programa que vai mostrar o resultado dos jogadores.
  // RESUMO DA PARTIDA
  printf("\n\n======== RESUMO DA PARTIDA ========\n\n");
  for (int i = 0; i < qtdJogadores - 1; i++) {
    if (jogadores[i].quit != 1) {
      printf("JOGADOR %i\n", i + 1);
      printf("-----------\n");

      if (jogadores[i].gameover == 1) {
        printf("PERDEU!\n");
      } else {
        if (jogadores[i].soma > 21) {//caso que o jogador tem mais que 21, ou seja perdeu com certeza.
          jogadores[i].gameover = 1;
          printf("PERDEU!\n");
        } else if ((mesa.soma > 21 || jogadores[i].soma > mesa.soma)) {//caso que ou a mesa passou de 21(perdeu) ou a soma do jogador eh maior que a mesa.
          jogadores[i].fichas += (jogadores[i].aposta_atual * 2);//dobram a aposta atual e devolvem.
          printf("GANHOU!\n");
        } else if (jogadores[i].soma < mesa.soma) {//soma da mesa maior que a do jogador e os dois menores que 21.
          jogadores[i].gameover = 1;
          printf("PERDEU!\n");
        } else {
          printf("Empate - fichas devolvidas\n");//se tiverem a mesma soma e com menos que 21.
          jogadores[i].fichas += jogadores[i].aposta_atual;//devolve apenas a aposta atual.
          jogadores[i].aposta_atual = 0;
        }
      }
      printf("\n\n");
    }
  }
}

void printRules() {//regras do jogo.
  printf("=========== REGRAS ===========\n\n");
  printf("BEM VINDO!\n\n");
  printf("Cada jogador comeca com 1250 fichas.\nSe todas forem perdidas o jogador eh eliminado.\n\n");
  printf("O jogador perde a rodada quando:\nA soma de suas cartas eh maior que 21.\nA soma das cartas da mesa eh maior que a soma dele.\n\n");
  printf("O jogador ganha a rodada quando:\nA soma de suas cartas eh maior que a soma das cartas da mesa.\n\n");
  printf("O jogador empata a rodada quando:\nA soma de suas cartas for igual a soma da mesa.\n\n");
  printf("Empate: As fichas apostadas sao devolvidas.\nVitoria: As fichas apostadas sao dobradas.\nDerrota: As fichas apostadas sao perdidas.\n\n");
}

void prosseguir() {//funcao para seguir, pedindo um caracter qualquer e depois limpando o console.
  printf("Digite qualquer caractere e de enter...\n");
  char temp;
  scanf(" %c",&temp);

  system("@cls||clear");
}

void saidajogadores(int qtdJogadores, PERSON jogadores[qtdJogadores]){//funcao para finalizar ou continuar o programa.
    for (int i = 0; i < qtdJogadores - 1; i++) {
        if (jogadores[i].quit != 1 && jogadores[i].fichas > 0) {
          char option;

          system("@cls||clear");
          printf("JOGADOR %i\n", i + 1);
          printf("-----------\n");
          printf("Deseja sair? (S ou N)\n");

          while (1) {
            scanf(" %c", &option);
            if (option != 'S' && option != 'N' && option != 's' && option != 'n')
              printf("Caractere invalido. Digite S ou N.\n");
            else
              break;
          }
          option = toupper(option);

          if (option == 'S') {
            jogadores[i].quit = 1;//caso todos jogadores estiver com .quit=1 o programa vai finalizar ou se todos jogadores estiverem com fichas.
          }
        }
      }
}
