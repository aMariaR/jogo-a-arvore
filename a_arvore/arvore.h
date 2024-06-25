//Arquivo que contém as funções de uma árvore binária de busca (ABB)
//Autor: Maria Rita Piekas
//mariaritapiekas@gmail.com
//Data de criação: 25/06/2024

#ifndef ARVORE_H
#define ARVORE_H

typedef struct No no;

//Função que cria um nó, faz seus filhos ser NULL e faz nó->palavra = p
no *cria_no(char *p);

//Função que retorna verdadeiro se o nó tem filhos NULL
bool no_sem_filhos(no *a);

//Função que retorna verdadeiro se nó = NULL
bool no_vazio(no *a);

//Função que retorna verdadeiro se o dado p existe na árvore
bool existe(no *a, char *p);

//Função que insere p na árvore
no *insere(no *a, char *p);

//Função que remove p da árvore
no *remove_no(no *a, char *p);

//Função que apaga a árvore inteira
void remove_arvore(no *a);

#endif