#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

indiceBst* inicializarIndiceBst(int indice, const char* nome) {
    indiceBst *novo = (indiceBst*)malloc(sizeof(indiceBst));
    novo->indice = indice;
    strncpy(novo->nome, nome, TAM_MAX_NOME - 1);
    novo->nome[TAM_MAX_NOME - 1] = '\0'; 
    return novo;
}

bst adicionarBst(indiceBst *valor, bst raiz) {
    if (raiz == NULL) {
        bst novo = (bst)malloc(sizeof(struct no_bst));
        novo->dado = valor;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }

    int comparacao = strcmp(valor->nome, raiz->dado->nome);

    if (comparacao > 0) {
        raiz->dir = adicionarBst(valor, raiz->dir);
    } else if (comparacao < 0) {
        raiz->esq = adicionarBst(valor, raiz->esq);
    }
    return raiz;
}

bst remover_bst(bst raiz, const char* nome) {
    if (raiz == NULL) {
        return raiz;
    }

    int comparacao = strcmp(nome, raiz->dado->nome);

    if (comparacao < 0) {
        raiz->esq = remover_bst(raiz->esq, nome);
    } else if (comparacao > 0) {
        raiz->dir = remover_bst(raiz->dir, nome);
    } else {
 
        if (raiz->esq == NULL) {
            bst temp = raiz->dir;
            free(raiz->dado);
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            bst temp = raiz->esq;
            free(raiz->dado);
            free(raiz);
            return temp;
        }


        bst temp = raiz->dir;
        while (temp->esq != NULL) {
            temp = temp->esq;
        }

        strcpy(raiz->dado->nome, temp->dado->nome);
        raiz->indice = temp->indice;

        raiz->dir = remover_bst(raiz->dir, temp->dado->nome);
    }
    return raiz;
}

int altura_bst(bst raiz) {
    if (raiz == NULL) {
        return 0;
    }
    return 1 + maior(altura_bst(raiz->dir), altura_bst(raiz->esq));
}

indiceBst* maior_elemento_bst(bst raiz) {
    if (raiz == NULL) {
        return NULL;
    }
    if (raiz->dir == NULL) {
        return raiz->dado;
    } else {
        return maior_elemento_bst(raiz->dir);
    }
}

indiceBst* menor_elemento_bst(bst raiz) {
    if (raiz == NULL) {
        return NULL;
    }
    if (raiz->esq == NULL) {
        return raiz->dado;
    } else {
        return menor_elemento_bst(raiz->esq);
    }
}

void pre_order_bst(bst raiz) {
    if (raiz != NULL) {
        imprimir_elemento_bst(raiz);
        pre_order_bst(raiz->esq);
        pre_order_bst(raiz->dir);
    }
}

void pos_order_bst(bst raiz) {
    if (raiz != NULL) {
        pos_order_bst(raiz->esq);
        pos_order_bst(raiz->dir);
        imprimir_elemento_bst(raiz);
    }
}

void in_order_bst(bst raiz) {
    if (raiz != NULL) {
        in_order_bst(raiz->esq);
        imprimir_elemento_bst(raiz);
        in_order_bst(raiz->dir);
    }
}

void imprimir_elemento_bst(bst raiz) {
    if (raiz != NULL) {
        printf("%s | ", raiz->dado->nome);
    }
}

int buscaIndiceBst(bst raiz, const char* nome) {
    if (nome != NULL && raiz != NULL) {
        int cmp = strcmp(nome, raiz->dado->nome);
        if (cmp == 0) {
            return raiz->dado->indice;
        } else {
            if (cmp > 0)
                return buscaIndiceBst(raiz->dir, nome);
            else
                return buscaIndiceBst(raiz->esq, nome);
        }
    } else {
        return -1;
    }
}
