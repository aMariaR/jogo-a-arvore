//Implementação do jogo de digitação de palavras em árvore
//Utiliza bibliotecas auxiliares
//Maria Rita Piekas
//mariaritapiekas@gmail.com

typedef struct Jogo {
  int pontos;
  no *raiz;
}


char *processa_teclado()
{
  
}


void jogo(Jogo j)
{
  char *p = sorteia_palavra();
  int tempo = (rand() % 14) + 1;
  while(tempo > 0) {
    //desenha o jogo (tempo, arvore, pontos)
    char *palavra_digitada = processa_teclado();
    if(existe(j->raiz, palavra_digitada)) {
      remove_no(j->raiz, palavra-digitada);
      j->pontos = calcula_pontos(palavra_digitada, tempo);
      return;
    }
    sleep(1);
    tempo--;
  }
  if((tempo == 0) || (!existe(raiz, palavra_digitada))) {
    insere_no(raiz, palavra_digitada);
    j->pontos = calcula_pontos('n', 0);
  }
  return;
}


void inicia_jogo()
{
  desenha_tela();
  desenha_texto();
  processa_teclado();  //espera enter pra começar
}



int main()
{
  srand(time(NULL));
  //cria a arvore
  no *raiz = cria_no("arvore");
  inicia_jogo();
  while() {
  jogo(raiz);
 }
}
