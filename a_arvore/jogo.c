//Implementação do jogo de digitação de palavras em árvore
//Utiliza bibliotecas auxiliares
//Maria Rita Piekas
//mariaritapiekas@gmail.com

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "arvore.h"
#include "sorteia.h"
#include "desenho.h"

struct Jogo_t {
  int pontos;
  no *raiz;
}; typedef struct Jogo_t Jogo;

void espera_enter()
{
  while (getchar() != '\n') {
    ; /* não faz nada */
  }
}

char *processa_teclado()
{
  char *palavra_digitada = (char *)malloc(15 * sizeof(char));
  scanf("%14s", palavra_digitada);
  return palavra_digitada;
}

void calcula_pontos(char *p, int t, Jogo *j)
{
  if((t <= 0) || (p == 'n')) {
    j->pontos = j->pontos - 15;
    return;
  }
  int tamanho = strlen(p);
  if (tamanho <= 5) {
    j->pontos = j->pontos + 10;
  } else if (tamanho <=10) {
    j->pontos = j->pontos + 15;
  } else {
    j->pontos = j->pontos + 20;
  } 
}

void jogo(Jogo *j)
{
  char *p = sorteia_palavra();
  int tempo = (rand() % 4) + 2;
  while(tempo > 0) {
    //desenha o jogo (tempo, arvore, pontos)
    char *palavra_digitada = processa_teclado();
    if(strcmp(palavra_digitada, "c") == 0) {
      exit(1);
    }
    if(existe(j->raiz, palavra_digitada)) {
      remove_no(j->raiz, palavra_digitada);
      calcula_pontos(palavra_digitada, tempo, j);
      return;
    }
    sleep(1);
    tempo--;
  }
  if((tempo == 0) || (!existe(j->raiz, palavra_digitada))) {
    insere_no(j->raiz, palavra_digitada);
    calcula_pontos('n', 0, j);
  }
  return;
}


void inicia_jogo()
{
  desenha_tela_inicio();    //retangulo colorido
  desenha_texto_inicio();   //centralizados a mensagem: para sair digite 'c'
  espera_enter();
}



int main()
{
  srand(time(NULL));
  //cria a arvore
  no *raiz = cria_no("arvore");
  inicia_jogo();
  while(!arvore_desequilibrada(raiz)) {
  jogo(raiz);
 }
  FILE *arq = fopen("pontos.txt", "w");
  if(arq == NULL) {
    printf("não foi possível abrir o arquivo");
    exit (1);
  }
  fputs(arq,"\npontos: %d", raiz->pontos);
  fclose(arq);
}
