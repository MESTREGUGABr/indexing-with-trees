#ifndef TABELA_H
#define TABELA_H

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
} RegistroJogo;

#endif
