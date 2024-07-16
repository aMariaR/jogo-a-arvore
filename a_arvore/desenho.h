#ifndef DESENHO_H
#define DESENHO_H

#include "arvore.h"

void desenha_tela_inicio();
void desenha_texto_inicio();
void calcula_posicao(no *raiz, int x, int y, int distancia);
void desenha_arvore(no *raiz);

#endif
