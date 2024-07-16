//Arquivo que contém implementação de uma árvore binária de busca (ABB)
//Autor: Maria Rita Piekas
//mariaritapiekas@gmail.com
//Data de criação: 04/06/2024

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "arvore.h"

no *cria_no(char *p)
{
  no *a = (no *)malloc(sizeof(no));
  if(a != NULL){
    a->esq = NULL;
    a->dir = NULL;
    strcpy(a->palavra, p);
    return a;
  } else { return NULL; }
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


no *insere_no(no *a, char *p)
{
  if (a == NULL) { 
    a = cria_no(p);
    return a;
  }
  if (strcmp(a->palavra, p) == 0) {
    return a; // Não insere duplicatas
  } else if (strcmp(a->palavra, p) < 0) {
    a->dir = insere_no(a->dir, p);
  } else {
    a->esq = insere_no(a->esq, p);
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


int altura(no *a) {
  if (a == NULL) return 0;
  int altura_esq = altura(a->esq);
  int altura_dir = altura(a->dir);
  return (altura_esq > altura_dir ? altura_esq : altura_dir) + 1;
}

bool arvore_desequilibrada(no *a) {
  if (a == NULL) return false;

  int altura_esq = altura(a->esq);
  int altura_dir = altura(a->dir);

  int diferenca = altura_esq - altura_dir;
  if (diferenca < 0) {
    diferenca = -diferenca; // Torna a diferença positiva
  }

  if (diferenca > 2) return true;

  return arvore_desequilibrada(a->esq) || arvore_desequilibrada(a->dir);
}