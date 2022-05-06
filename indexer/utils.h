#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#ifndef INDEXER_UTILS_H
#define INDEXER_UTILS_H

#endif

typedef char *string;

void palavraParaMinusculo(char palavra[64]);

bool ehPalavraValida(string palavra);

char **separacaoString(char *termo, const char delimitador);

double calcularTF(int qtd, int total_palavras);

double calcularIDF(int total_arquivos, int total_arquivos_com_palavras);

double calcularTFIDF(int qtd, int total_palavras, int total_arquivos, int total_arquivos_com_palavras);
