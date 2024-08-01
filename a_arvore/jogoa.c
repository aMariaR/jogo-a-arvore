//joguinho da árvore
//compila com gcc -o jogoa jogoa.c arvore.c desenho.c sorteia.c telag.c -lallegro_font -lallegro_color -lallegro_ttf -lallegro_primitives -lallegro


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include "arvore.h"
#include "sorteia.h"
#include "telag.h"
#include "desenho.h"

struct Jogo_t {
    int pontos;
    no *r;
}; typedef struct Jogo_t Jogo;

void espera_enter() {
    while (getchar() != '\n') {
        ; /* não faz nada */
    }
}

char *processa_teclado() {
    char *palavra_digitada = (char *)malloc(15 * sizeof(char));
    scanf("%14s", palavra_digitada);
    return palavra_digitada;
}

void calcula_pontos(char *p, int t, Jogo *j) {
    if(t <= 0) {
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


void jogo(Jogo *j, char *p) {
    int tempo = (rand() % 3) + 5;
    char *palavra_digitada = NULL;
    double tempo_inicio, tempo_atual;
    tempo_inicio = tela_relogio();

    while(tempo > 0) {
        // Desenha o jogo árvore
        calcula_posicao(j->r, 400, 50, 200);
        desenha_arvore(j->r);

        // Desenha o tempo restante no canto superior esquerdo
        char tempo_str[16];
        sprintf(tempo_str, "Tempo: %d", tempo);
        tela_texto(100, 10, 14, branco, tempo_str);

        // Desenha a palavra a ser digitada no canto superior direito
        tela_texto(300, 10, 14, branco, "palavra a ser digitada:");
        tela_texto(450, 10, 14, branco, p);

        // Desenha os pontos
        char dpontos[11];
        sprintf(dpontos, "Pontos: %d", j->pontos);
        tela_texto(600, 10, 14, branco, dpontos);

        tela_atualiza();

        palavra_digitada = (char *)malloc(15 * sizeof(char));
        palavra_digitada = processa_teclado();
        if(strcmp(palavra_digitada, "c") == 0) {
            exit(1);
        }
        if(strcmp(p, palavra_digitada) == 0) {
            desenha_arvore(j->r);
            tela_atualiza();
            calcula_pontos(palavra_digitada, tempo, j);
            return;
        }

        sleep(1);
        tempo_atual = tela_relogio();
        tempo = (int)(tempo_inicio + (rand() % 3) + 2 - tempo_atual);
        
    }
    if(tempo <= 0) {
        insere_no(j->r, p);
        calcula_pontos("n", 0, j);
        desenha_arvore(j->r);
        tela_atualiza();
    }
    return;
}

void inicia_jogo() {
    desenha_tela_inicio(); 
    desenha_texto_inicio();   // Centralizados a mensagem: para sair digite 'c'
    tela_atualiza();
    espera_enter();
}

int main() {
    srand(time(NULL));
    tela_inicio(800, 600, "Árvore Binária");
    no *raiz = cria_no("minha_arvore");
    Jogo *j = (Jogo *)malloc(sizeof(Jogo));
    j->pontos = 0;
    j->r = raiz;
    char *p = (char *)malloc(15 *sizeof(char));
    inicia_jogo();

    while(!arvore_desequilibrada(j->r)) {
        p = sorteia_palavra();
        jogo(j, p);
    }

    FILE *arq = fopen("pontos", "w");
    if(arq == NULL) {
        printf("não foi possível abrir o arquivo");
        exit(1);
    }
    fprintf(arq, "\npontos: %d", j->pontos);
    fclose(arq);

    tela_fim();
    return 0;
}
