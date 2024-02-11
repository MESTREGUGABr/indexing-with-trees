#ifndef TABELA_H
#define TABELA_H
#include "../arvores/bst.h"
#include "../arvores/bst.c"
#include "../arvores/rb.h"
#include "../arvores/rb.c"
#include "../arvores/avl.h"
#include "../arvores/avl.c"
#include <stdio_ext.h>

enum tipo_arvore {BST, AVL, RB};
typedef enum tipo_arvore tipo_arvore;

#define TAM_MAX_NOME 50

typedef enum {
    COMPLETO,
    PARCIAL,
    INCOMPLETO
} EstadoJogo;

typedef struct {
    char nome[TAM_MAX_NOME];
    char dataLancamento[TAM_MAX_NOME];
    EstadoJogo estado;
    float nota;
    int horasJogadas;
    char desenvolvedora[TAM_MAX_NOME];
} RegistroJogo;

typedef struct tabela {
    FILE *arquivo_dados;
    bst indiceBst;
    avl indice_avl;
    rb indice_rb;
} tabela;

int inicializarTabela(tabela *tab);

int inserir_jogo(tabela *tab, RegistroJogo *jogo);
void remover_jogo(tabela *tab, int indice);
dado buscar_jogo(FILE *arq, int chave);

void salvar_jogo(FILE *arq, RegistroJogo *jogo);
void imprimir_elemento(RegistroJogo jogo);
void listar_por_nome(FILE *arq, bst raiz);
void listar_por_codigo(FILE *arq, avl raiz);
void listar_por_descricao(FILE *arq, rb raiz);

void salvar_arquivoBst(char *nome, bst a);
void salvar_auxiliarBst(bst raiz, FILE *arq);

void salvar_arquivo_avl(char *nome, avl a);
void salvar_auxiliar_avl(avl raiz, FILE *arq);

void salvar_arquivo_rb(char *descricao, rb a);
void salvar_auxiliar_rb(rb raiz, FILE *arq);

void carregar_arquivo_arvore(tabela *tab, tipo_arvore tipo);

dado* ler_dados();
void tirar_enter(char *string);
void finalizar (tabela *tab);

#endif
