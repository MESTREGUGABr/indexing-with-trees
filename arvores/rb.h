#ifndef RB_H
#define RB_H
#include <stdlib.h>
#define TAM_MAX_NOME 50

enum cor { VERMELHO, PRETO, DUPLO_PRETO };

typedef struct indice_ {
	char desenvolvedora[TAM_MAX_NOME];
	int indice;
}indice_rb;

typedef struct no_rb {
	indice_rb *dado;
	enum cor cor;
	struct no_rb *esq, *dir, *pai;
}no_rb;

typedef no_rb* rb;


indice_rb* inicializar_indice_rb(int indice, char *descricao);
void inicializar_rb(rb *raiz);
void inserir_rb(rb *raiz, indice_rb *valor);
void remover_rb(rb *raiz, rb* raiz_relativa, char *descricao);
int altura_rb(rb raiz);
void imprimir_rb(rb raiz);
void imprimir_elemento_rb(rb raiz);
int buscar_indice_rb(rb raiz, char* descricao);

enum cor cor_rb(rb elemento);
int eh_raiz_rb(rb elemento);
int eh_filho_esquerdo_rb(rb elemento);
int eh_filho_direito_rb(rb elemento);
indice_rb* maior_elemento_rb(rb raiz);
rb eh_irmao_rb(rb elemento);
rb tio_rb(rb elemento);
int maior_rb(int a, int b);

void ajustar_rb(rb *raiz, rb elemento);
void rotacao_simples_direita_rb(rb *raiz, rb pivo);
void rotacao_simples_esquerda_rb(rb *raiz, rb pivo);
void reajustar_rb(rb *raiz, rb elemento);
void retira_duplo_preto_rb(rb *raiz, rb elemento);
void preorder_rb(rb a);
#endif