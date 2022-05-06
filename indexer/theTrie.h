#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "utils.h"

typedef char *string;

typedef struct node {
    struct node *children[26];
    int count;
    bool isFinalWord;
} node;

typedef struct Palavras {
    double count;
    char word[64];
} Palavras;

node *novoNo(void);

void inserirTrie(string palavra, node *trie);

bool pesquisaComContagem(string palavra, node *trie, int *repeat);

void geraTrieArquivo(string nome_arquivo, node *trie_busca, int n, Palavras *tops);

int contadorPalavras(node *trie_busca, char *termo);

int contadorPalavrasTotal(node *head);



