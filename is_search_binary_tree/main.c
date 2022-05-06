#include <stdio.h>
#include <stdlib.h>

typedef struct arvore {
    char info;
    struct arvore *esq;
    struct arvore *dir;
} Arvore;


Arvore*  cria_arv_vazia (void);
Arvore*  arv_constroi (char c, Arvore* e, Arvore* d);
int      verifica_arv_vazia (Arvore* a);
Arvore*  arv_libera (Arvore* a);
void     arv_imprime (Arvore* a);
int arv_bin_check(Arvore *a, Arvore *min, Arvore *max);

Arvore* cria_arv_vazia (void) {
    return NULL;
}

Arvore* arv_constroi (char c, Arvore* e, Arvore* d) {
    Arvore* a = (Arvore*)malloc(sizeof(Arvore));
    a->info = c;
    a->esq = e;
    a->dir = d;
    return a;
}

int verifica_arv_vazia (Arvore* a) {
    return (a == NULL);
}

Arvore* arv_libera (Arvore* a) {
    if (!verifica_arv_vazia(a)) {
        arv_libera (a->esq);
        arv_libera (a->dir);
        free(a);
    }
    return NULL;
}

void arv_imprime (Arvore* a) {
	if(!a) return;

	arv_imprime(a->esq);
    printf("%c ", a->info);
	arv_imprime(a->dir);
}

int arv_bin_check(Arvore *a, Arvore *min, Arvore *max) {
    if (a == NULL)
        return 1;

    if ((min != NULL && a->info <= min->info) || (max != NULL && a->info >= max->info))
        return 0;

    return arv_bin_check(a->esq, min, a) &&
           arv_bin_check(a->dir, a, max);
}

int main () {
    Arvore *arvBusca    = arv_constroi('4', cria_arv_vazia(), cria_arv_vazia());
    arvBusca->esq       = arv_constroi('2', cria_arv_vazia(), cria_arv_vazia());
    arvBusca->esq->esq  = arv_constroi('1', cria_arv_vazia(), cria_arv_vazia());
    arvBusca->esq->dir  = arv_constroi('3', cria_arv_vazia(), cria_arv_vazia());
    arvBusca->dir       = arv_constroi('6', cria_arv_vazia(), cria_arv_vazia());
    arvBusca->dir->esq  = arv_constroi('5', cria_arv_vazia(), cria_arv_vazia());
    arvBusca->dir->dir  = arv_constroi('7', cria_arv_vazia(), cria_arv_vazia());
    arv_imprime(arvBusca);
    printf("\n%d\n", arv_bin_check(arvBusca, NULL, NULL));

    Arvore *arvBuscaErrada    = arv_constroi('4', cria_arv_vazia(), cria_arv_vazia());
    arvBuscaErrada->esq       = arv_constroi('3', cria_arv_vazia(), cria_arv_vazia());
    arvBuscaErrada->esq->esq  = arv_constroi('6', cria_arv_vazia(), cria_arv_vazia());
    arvBuscaErrada->esq->dir  = arv_constroi('2', cria_arv_vazia(), cria_arv_vazia());
    arvBuscaErrada->dir       = arv_constroi('1', cria_arv_vazia(), cria_arv_vazia());
    arvBuscaErrada->dir->esq  = arv_constroi('7', cria_arv_vazia(), cria_arv_vazia());
    arvBuscaErrada->dir->dir  = arv_constroi('5', cria_arv_vazia(), cria_arv_vazia());
    arv_imprime(arvBuscaErrada);
    printf("\n%d\n", arv_bin_check(arvBuscaErrada, NULL, NULL));
  return 0;
}
