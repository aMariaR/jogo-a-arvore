#include <stdio.h>
#include <stdbool.h>
#include "telag.h"
#include "arvore.h"

void desenha_tela_inicio() {
    tela_inicio(800, 600, "Árvore Binária");
}

void desenha_texto_inicio() {
    tela_texto(300, 10, 14, branco, "Para sair digite 'c', para iniciar digite 'enter'");
}

void calcula_posicao(no *raiz, int x1, int y1, int distancia) {
    if (raiz == NULL) return;

    raiz->x = x1;
    raiz->y = y1;
    printf("Calculando posição: %s (%d, %d)\n", raiz->palavra, x1, y1);

    if (raiz->esq != NULL) {
        calcula_posicao(raiz->esq, x1 - distancia, y1 + 50, distancia / 2);
    }
    if (raiz->dir != NULL) {
        calcula_posicao(raiz->dir, x1 + distancia, y1 + 50, distancia / 2);
    }
}

void desenha_arvore(no *raiz) {
    if (raiz == NULL) return;

    // Desenha conexões
    if (raiz->esq != NULL) {
        tela_linha(raiz->x, raiz->y, raiz->esq->x, raiz->esq->y, 2, branco);
        desenha_arvore(raiz->esq);
    }
    if (raiz->dir != NULL) {
        tela_linha(raiz->x, raiz->y, raiz->dir->x, raiz->dir->y, 2, branco);
        desenha_arvore(raiz->dir);
    }

    // Desenha o nó
    tela_texto(raiz->x, raiz->y, 20, branco, raiz->palavra);
    printf("Desenhando nó: %s (%d, %d)\n", raiz->palavra, raiz->x, raiz->y);
}
