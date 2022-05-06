#include <assert.h>
#include <ctype.h>
#include "utils.h"

void palavraParaMinusculo(char palavra[64]) {
    int i, j;
    for (i = 0; palavra[i] != '\0'; ++i) {
        while (!((palavra[i] >= 'a' && palavra[i] <= 'z') || (palavra[i] >= 'A' && palavra[i] <= 'Z') ||
                 palavra[i] == '\0')) {
            for (j = i; palavra[j] != '\0'; ++j) {
                palavra[j] = palavra[j + 1];
            }
            palavra[j] = '\0';
        }
        palavra[i] = tolower(palavra[i]);
    }
}

bool ehPalavraValida(string palavra) {
    int tamanhoPalavra = strlen(palavra);

    if (tamanhoPalavra <= 2)
        return false;

    return true;
}

char **separacaoString(char *termo, const char delimitador) {
    char **result = 0;
    size_t count = 0;
    char *temp = termo;
    char *ultimo_delimitador = 0;
    char delim[2];
    delim[0] = delimitador;
    delim[1] = 0;

    while (*temp) {
        if (delimitador == *temp) {
            count++; //contador de elementos a serem divididos
            ultimo_delimitador = temp;
        }
        temp++;
    }

    count += ultimo_delimitador < (termo + strlen(termo) - 1); //Tratamento do token final
    count++;

    result = malloc(sizeof(char *) * count);

    if (result) {
        size_t idx = 0;
        char *token = strtok(termo, delim);

        while (token) {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}


double calcularTF(int qtd, int total_palavras) {

    if (total_palavras == 0)
        return 0;

    return (double) qtd / (double) total_palavras;

}

double calcularIDF(int total_arquivos, int total_arquivos_com_palavras) {
    if (total_arquivos_com_palavras == 0)
        return 0;
    double x = (double) (total_arquivos / total_arquivos_com_palavras);
    return log10(x);

}


double calcularTFIDF(int qtd, int total_palavras, int total_arquivos, int total_arquivos_com_palavras) {
    double tf = calcularTF(qtd, total_palavras);
    double idf = calcularIDF(total_arquivos, total_arquivos_com_palavras);
    return (tf * idf);
}
