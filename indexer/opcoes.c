#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "opcoes.h"
#include "theTrie.h"

void opcaoFreq(string vetor_args[]) {
    printf("Opção \"--freq\" escolhida\n");
    node *trie = novoNo();
    int qtd = strtol(vetor_args[2], NULL, 10);
    Palavras *ranking = (Palavras *) malloc(sizeof(Palavras) * (qtd));
    geraTrieArquivo(vetor_args[3], trie, qtd, ranking);
    printf("\n%d termos mais presentes no arquivo:\n", qtd);
    for (int i = 0; i < qtd; i++) {
        printf("%dº | %s | %.0f vezes\n", i + 1, ranking[i].word, ranking[i].count);
    }
}

void opcaoFreqWord(string nomeArquivo, string termoBusca) {
    printf("Opção \"--freq-word\" escolhida\n");
    node *trie = novoNo();

    geraTrieArquivo(nomeArquivo, trie, 0, NULL);

    int frequencia_encontrada;

    if (pesquisaComContagem(termoBusca, trie, &frequencia_encontrada)) {
        printf("A palavra %s foi encontrada %d vezes no arquivo!\n", termoBusca, frequencia_encontrada);
    } else {
        printf("A palavra %s não foi encontrada no arquivo!\n", termoBusca);
    }
}

void opcaoSearch(int cont_args, string vetor_args[]) {
    printf("Opção \"--search\" escolhida\n");
    int qtd_arquivos = (cont_args - 3);
    int qtd_termos = 0;
    node **trie_busca = malloc(sizeof(node) * qtd_arquivos); //Implementa trie de busca

    Palavras *relevancia_por_arquivo; //Foi utilizado o Palavras pois a estrutura é suficiente para armazenar o tipo de dado necessário para o armazenamento e ordenação da relevância
    relevancia_por_arquivo = (Palavras *) malloc(sizeof(Palavras) * (qtd_arquivos));

    char **termos;
    termos = separacaoString(vetor_args[2], ' ');
    for (int i = 0; *(termos + i); i++) qtd_termos++;

    int palavras_no_termo = 1;
    for (int i = 0; *(termos + i); i++) {
        palavras_no_termo++;
    }

    int **arquivos_com_palavras = malloc(sizeof(int *) * qtd_arquivos);
    for (int i = 0; i < qtd_arquivos + 2; i++) {
        arquivos_com_palavras[i] = malloc(sizeof(int *) * palavras_no_termo);
    }

    for (int i = 0; i < qtd_arquivos; i++) {// Leitura de arquivos e inserção na trie de busca
        trie_busca[i] = novoNo();
        geraTrieArquivo(vetor_args[i + 3], trie_busca[i], 0, NULL);

        if (termos != NULL) {
            for (int j = 0; *(termos + j); j++) {
                int value;
                pesquisaComContagem(*(termos + j), trie_busca[i], &value);
                if (value > 0) {
                    arquivos_com_palavras[i][j]++; //Contagem de arquivos com palavras
                }
            }
        }
        strcpy(relevancia_por_arquivo[i].word, vetor_args[i + 3]);
    }

    for (int i = 0; i < qtd_arquivos; i++) { //Calculo TFIDF
        int qtd_palavras = contadorPalavrasTotal(trie_busca[i]);
        relevancia_por_arquivo[i].count = 0;
        if (termos) {
            for (int j = 0; *(termos + j); j++) {
                int count = contadorPalavras(trie_busca[i], *(termos + j));
                relevancia_por_arquivo[i].count += calcularTFIDF(count, qtd_palavras, qtd_arquivos,
                                                                 arquivos_com_palavras[i][j]);
            }
        }
        relevancia_por_arquivo[i].count =
                ((double) relevancia_por_arquivo[i].count / qtd_termos) * 100; //media dos termos
    }

    for (int i = 0; i < qtd_arquivos; i++) { //Calculo TFIDF
        printf("O arquivo %s é %f%% relevante segundo TFIDF\n", relevancia_por_arquivo[i].word,
               relevancia_por_arquivo[i].count);
    }
}