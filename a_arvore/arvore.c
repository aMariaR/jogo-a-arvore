//Arquivo que contém implementação de uma árvore binária de busca (ABB)
//Autor: Maria Rita Piekas
//mariaritapiekas@gmail.com
//Data de criação: 04/06/2024

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "arvore.h"

#define TAM_MAX_PALAVRAS 15

struct No {
  char palavra[TAM_MAX_PALAVRAS];
  struct No *esq;
  struct No *dir;
};


no *cria_no(char *p)
{
  no *a = (no *)malloc(sizeof(no));
  if(a != NULL){
    a->esq = NULL;
    a->dir = NULL;
    strcpy(a->palavra, p);
    return a;
  }
}


bool no_sem_filhos(no *a)
{
  return((a->esq == NULL) && (a->dir == NULL));
}


bool no_vazio(no *a)
{
  return(a == NULL);
}


bool existe(no *a, char *p)
{
  if(no_vazio(a)) return 0;
  if(strcmp(a->palavra, p) == 0) return 1;
  return(existe(a->esq, p) || existe(a->dir, p));
}


no *insere(no *a, char *p)
{
  if (a == NULL) { 
    a = cria_no(p);
    return a;
  }
  if (strcmp(a->palavra, p) == 0) {
    return a; // Não insere duplicatas
  } else if (strcmp(a->palavra, p) < 0) {
    a->dir = insere(a->dir, p);
  } else {
    a->esq = insere(a->esq, p);
  }
  return a;
}


no *remove_no(no *a, char *p)
{
  if ( a == NULL) {
    return NULL;
  }
  if (strcmp(a->palavra, p) < 0) {
    a->dir = remove_no(a->dir, p);
  } else if (strcmp(a->palavra, p) > 0) {
    a->esq = remove_no(a->esq, p);
  } else {
        // Nó encontrado
    if (no_sem_filhos(a)) {
        free(a);
        a = NULL;
    } else if (a->esq == NULL) {
        no *b = a;
        a = a->dir;
        free(b);
    } else if (a->dir == NULL) {
        no *b = a;
        a = a->esq;
        free(b);
    } else {
        no *b = a->esq;
        while ( b->dir != NULL) {
            b = b->dir;
        }
        strcpy(a->palavra, b->palavra);
        a->esq = remove_no(a->esq, b->palavra);
    }

  }
    return a;
}


void remove_arvore(no *a)
{
  if (a != NULL) {
    remove_arvore(a->esq);
    remove_arvore(a->dir);
    free(a);
  }
}
