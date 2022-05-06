#include "theTrie.h"

#define convertToIndex(c) ((int)c - (int)'a')

node *novoNo(void) {
    node *pNode = NULL;
    pNode = (node *) malloc(sizeof(node));
    if (pNode) {
        int i;
        pNode->isFinalWord = false;
        for (i = 0; i < 26; i++)
            pNode->children[i] = NULL;
    }
    return pNode;
}


void inserirTrie(string palavra, node *trie) {
    int altura;
    int tamanho_palavra = strlen(palavra);
    int index;

    node *no_trie = trie;

    for (altura = 0; altura < tamanho_palavra; altura++) {
        index = convertToIndex(palavra[altura]);
        if (!no_trie->children[index])
            no_trie->children[index] = novoNo();

        no_trie = no_trie->children[index];
    }


    no_trie->isFinalWord = true;
    no_trie->count++;

}

bool pesquisaComContagem(string palavra, node *trie, int *repeat) {
    int altura;
    int tamanho_palavra;
    tamanho_palavra = strlen(palavra);
    int index;
    node *no_trie = trie;
    for (altura = 0; altura < tamanho_palavra; altura++) {
        index = convertToIndex(palavra[altura]);
        if (!no_trie->children[index])
            return false;
        no_trie = no_trie->children[index];
    }
    *repeat = no_trie->count;
    return (no_trie->isFinalWord);
}


int contadorPalavras(node *trie_busca, char *termo) {
    if (trie_busca == NULL)
        return 0;
    node *atual = trie_busca;

    while (*termo) {
        atual = atual->children[*termo - 'a'];
        if (atual == NULL)
            return 0;
        termo++;
    }
    return atual->count;
}


void geraTrieArquivo(string nome_arquivo, node *trie_busca, int n, Palavras *tops) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    char buffer[512];
    int countAux;
    char bufferAux[512];
    printf("Processando %s. Aguarde...\n", nome_arquivo);
    while (fscanf(arquivo, "%s", buffer) != EOF) {
        palavraParaMinusculo(buffer);

        if (!ehPalavraValida(buffer)) 
            continue;

        inserirTrie(buffer, trie_busca);
        int count = contadorPalavras(trie_busca, buffer);
        for (int i = 0; i < n; i++) {
            if (count > tops[i].count) {
                countAux = tops[i].count;
                strcpy(bufferAux, tops[i].word);

                tops[i].count = count;
                strcpy(tops[i].word, buffer);

                if (strcmp(bufferAux, buffer) == 0)
                    break;

                for (int j = i+1; j < n; j++){
                    if (strcmp(tops[j].word, buffer) == 0)
                        tops[j].count = -1;
                }

                count = countAux;
                strcpy(buffer, bufferAux);
            }
        }
    }
    fclose(arquivo);
}


int contadorPalavrasTotal(node *trie_busca) {
    int result = 0;

    if (trie_busca->isFinalWord) //caso final da palavra
        result += trie_busca->count;

    for (int i = 0; i < 26; i++)
        if (trie_busca->children[i])
            result += contadorPalavrasTotal(trie_busca->children[i]);
    return result;
}
