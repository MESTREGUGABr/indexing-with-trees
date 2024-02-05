#ifndef BST_H
#define BST_H
#include "tabela.h"

typedef struct indiceBst {
    char nome[TAM_MAX_NOME];
    int indice;
} indiceBst;

typedef struct no_bst {
    indiceBst *dado;
    struct no_bst *esq, *dir;
} no_bst;

typedef no_bst * bst;

indiceBst* inicializarIndiceBst(int indice, const char* nome);
bst adicionarBst(indiceBst *valor, bst raiz);
int altura_bst(bst raiz);
indiceBst* maior_elemento_bst(bst raiz);
indiceBst* menor_elemento_bst(bst raiz);
void pre_order_bst(bst raiz);
void pos_order_bst(bst raiz);
void in_order_bst(bst raiz);
bst remover_bst(bst raiz, const char* nome);
void imprimir_elemento_bst(bst raiz);
int buscaIndiceBst(bst raiz, const char* nome);

#endif
