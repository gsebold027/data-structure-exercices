#include <stdio.h>
#include <string.h>
#include "theTrie.h"
#include "utils.h"
#include "opcoes.h"

int main(int argc, string argv[]) {
    if (argc <= 3) {
        printf("Indexer\n");
        printf("Opções:\n");
        printf("--freq N ARQUIVO -> Exibe o número de ocorrência das N palavras que mais aparecem em ARQUIVO, em ordem decrescente de ocorrência.\n");
        printf("--freq-word PALAVRA ARQUIVO -> Exibe o número de ocorrências de PALAVRA em ARQUIVO. \n");
        printf("--search TERMO ARQUIVO [ARQUIVO ...] -> Exibe uma listagem dos ARQUIVOS mais relevantes encontrados pela busca por TERMO. A listagem é apresentada em ordem descrescente de relevância. TERMO pode conter mais de uma palavra. Neste caso, deve ser indicado entre àspas.\n");
        printf("\nDescição:\n");
        printf("O programa **indexer** realiza uma contagem de palavras em documentos de texto.\nA partir dessa contagem, ele ainda permite uma busca pelo número de ocorrências de uma palavra específica em um documento, ou a seleção de documentos relevantes para um dado termo de busca.\nO programa **indexer** transforma todas as letras para minúsculas e ignora caracteres como números e pontuações.\nQuando executado com a opção --freq, o programa **indexer** irá exibir o número de ocorrências das N palavras mais frequentes no documento passado como parâmetro, em ordem decrescente de ocorrências.\Quando executado com a opção --freq-word, o programa **indexer** exibe a contagem de uma palavra específica no documento passado como parâmetro.Por fim, quando executado com a opção --search, o programa **indexer** apresenta uma listagem dos documentos mais relevantes para um dado termo de busca.\nPara tanto, o programa utiliza o cálculo TF-IDF (Term Frequency-Inverse Document Frequency).");
    } else if (strcmp(argv[1], "--freq") == 0) {
        opcaoFreq(argv);
    } else if (strcmp(argv[1], "--freq-word") == 0) {
        opcaoFreqWord(argv[3], argv[2]);
    } else if (strcmp(argv[1], "--search") == 0) {
        opcaoSearch(argc, argv);
    } else {
        printf("Os parâmetros apresentados estão errados. Verifique a opção desejada e tente novamente\n");
    }
}
