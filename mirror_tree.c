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
int      arv_pertence (Arvore* a, char c);
void     arv_imprime (Arvore* a);
Arvore * cria_espelho(Arvore * arv_a);
int eh_espelho (Arvore* a, Arvore* b);


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

int arv_conta (Arvore* a){
	if(!a) return(0);

	return(1 + arv_conta(a->esq) + arv_conta(a->dir));
}

void arv_imprime (Arvore* a){
	if(!a) return;

	arv_imprime(a->esq);
	arv_imprime(a->dir);
	printf("%c ", a->info);
}

Arvore * cria_espelho(Arvore * arv_a) {
    if (arv_a == NULL)
        return NULL;

    return arv_constroi(arv_a->info, cria_espelho(arv_a->dir), cria_espelho(arv_a->esq));
}

int eh_espelho (Arvore* a, Arvore* b) {
	if (a == NULL && b == NULL)
        return 1;

    if (a == NULL || b == NULL)
        return 0;


    if ( a->info == b->info && eh_espelho(a->esq, b->dir) && eh_espelho(a->dir, b->esq) )
        return 1;

    return 0;
}

int main (int argc, char *argv[]) {
    Arvore *a, *a1, *a2, *a3, *a4, *a5;
    a1 = arv_constroi('d',cria_arv_vazia(),cria_arv_vazia());
    a2 = arv_constroi('b',cria_arv_vazia(),a1);
    a3 = arv_constroi('e',cria_arv_vazia(),cria_arv_vazia());
    a4 = arv_constroi('f',cria_arv_vazia(),cria_arv_vazia());
    a5 = arv_constroi('c',a3,a4);
    a  = arv_constroi('a',a2,a5);
	arv_imprime(a);
	printf("\n");

    Arvore *b;
    b = cria_espelho(a);
    arv_imprime(b);
    printf("\n");

    if (eh_espelho(a, b)) {
        printf("arvores a e b são espelho");
    } else {
        printf("arvores a e b não são espelho");
    }

    printf("\n");

    if (eh_espelho(a, a)) {
        printf("arvores a e a são espelho");
    } else {
        printf("arvores a e a não são espelho");
    }

  return 0;
}
