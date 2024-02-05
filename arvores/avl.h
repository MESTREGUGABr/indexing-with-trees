#ifndef AVL_H
#define AVL_H
#include <stdlib.h>

typedef struct indice_avl {
    char data_lancamento[20]; 
    int indice; 
} indice_avl;

typedef struct no_avl {
    int fb;
    indice_avl *dado;
    struct no_avl *esq, *dir;
} no_avl;

typedef no_avl *avl;

indice_avl *inicializar_indice_avl(char *data_lancamento, int indice);

avl adicionar_avl(avl a, indice_avl *v, int *cresceu);

int comparar_datas(char *data1, char *data2);

int buscar_indice_avl(avl raiz, char *data_lancamento);

avl remover_elemento_avl(avl a, char *data_lancamento, int *diminuiu);

avl rotacao_avl(avl a);

avl rotacao_simples_direita_avl(avl a);

avl rotacao_simples_esquerda_avl(avl a);

avl rotacao_dupla_direita_avl(avl a);

avl rotacao_dupla_esquerda_avl(avl a);

void pre_order_avl(avl raiz);

void pos_order_avl(avl raiz);

void in_order_avl(avl raiz);

void imprimir_elemento_avl(avl raiz);

#endif
