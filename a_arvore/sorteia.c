#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char sorteia_letra()
{
    char letra;
    int v = rand() % 26;
    letra = 'a' + v;
    return letra;
}

char *sorteia_silaba()
{
    int n_letras = (rand() % 3) + 1; // Garante que haja pelo menos 1 letra
    char *silaba = (char *)malloc((n_letras + 1) * sizeof(char));
    for (int i = 0; i < n_letras; i++) {
        silaba[i] = sorteia_letra();
    }
    silaba[n_letras] = '\0'; // Terminador nulo
    return silaba;
}

char *sorteia_palavra()
{
    int numero_silabas = (rand() % 5) + 1; // Garante que haja pelo menos 1 sílaba
    char *palavra = (char *)malloc(15 * sizeof(char));
    palavra[0] = '\0'; // Inicializa a string com o terminador nulo

    for (int i = 0; i < numero_silabas; i++) {
        char *silaba = sorteia_silaba();
        strcat(palavra, silaba);
        free(silaba); // Libera a memória da sílaba após uso
    }

    return palavra;
}

int main() {
    srand(time(NULL));
    char *palavra = sorteia_palavra();
    printf("%s\n", palavra);
    free(palavra); // Libera a memória da palavra após uso
    return 0;
}
