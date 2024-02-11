#include <stdio.h>
#include <stdlib.h>
#include "tabela.h"
#include <string.h>

int inicializarTabela(tabela *tab) {
	tab->arquivo_dados = fopen("dados.dat", "r+b");
	tab->indiceBst  = NULL;
	tab->indice_avl = NULL;
	inicializar_rb(&tab->indice_rb);
	carregar_arquivo_arvore(tab, BST);
	carregar_arquivo_arvore(tab, AVL);
	carregar_arquivo_arvore(tab, RB);
	if(tab->arquivo_dados != NULL)
		return 1;
	else
		return 0;
}
void tirar_enter(char *string) {
	string[strlen(string) -1] = '\0';
}

int inserir_jogo(tabela *tab, RegistroJogo *jogo) {
	int posicaoNovoRegistro, retorno;
	retorno = tab->arquivo_dados != NULL;
	if(retorno) {
		fseek(tab->arquivo_dados, 0L, SEEK_END);
		posicaoNovoRegistro = ftell(tab->arquivo_dados);
		tab->indiceBst = adicionarBst(inicializarIndiceBst(posicaoNovoRegistro, jogo->nome), tab->indiceBst);
		tab->indice_avl = adicionar_avl(tab->indice_avl, inicializar_indice_avl(posicaoNovoRegistro, jogo->dataLancamento), NULL);
		inserir_rb(&tab->indice_rb, inicializar_indice_rb(posicaoNovoRegistro, jogo->desenvolvedora));

		salvar_jogo(tab->arquivo_dados, jogo);
	}

	return retorno;
}

void salvar_jogo(FILE *arq, RegistroJogo *jogo) {
    fprintf(arq, "%s;%s;", jogo->nome, jogo->dataLancamento);

    switch (jogo->estado) {
        case COMPLETO:
            fprintf(arq, "Completo,");
            break;
        case PARCIAL:
            fprintf(arq, "Parcial,");
            break;
        case INCOMPLETO:
            fprintf(arq, "Incompleto,");
            break;
        default:
            fprintf(arq, "Indefinido,");
            break;
    }

    fprintf(arq, "%.2f;%d\n", jogo->nota, jogo->horasJogadas);
}

void remover_jogo(tabela* tab, int indice) {
    if (tab != NULL) {
        RegistroJogo jogo = buscar_jogo(tab->arquivo_dados, indice);

        if (!jogo.removido) {
            tab->indiceBst = remover_bst(tab->indiceBst, jogo.nome);
            tab->indice_avl = remover_avl(tab->indice_avl, jogo.dataLancamento);
            remover_rb(&tab->indice_rb, &tab->indice_rb, jogo.desenvolvedora);

            fseek(tab->arquivo_dados, indice, SEEK_SET);
            char removido = '1';
            fwrite(&removido, sizeof(char), 1, tab->arquivo_dados);
            fseek(tab->arquivo_dados, 0L, SEEK_END);
        } else {
            printf("Erro ao remover\n");
        }
    }
}

char* tipo_enum(int tipo) {
	switch(tipo) {
		case 0:
			return "Completo";
		case 1:
			return "Parcial";
		case 2:
			return "Incompleto";
		
	}
}

RegistroJogo* ler_dados() {
    RegistroJogo* novo = (RegistroJogo*)malloc(sizeof(RegistroJogo));

    printf("Nome: ");
    scanf(" %[^\n]%*c", novo->nome);

    printf("Data de Lançamento: ");
    scanf(" %[^\n]%*c", novo->dataLancamento);

    int op;
    printf("Estado: ");
    while (scanf("%d", &op) != 1 || op < 1 || op > 3) {
        printf("Insira um numero entre 1 e 3: ");
        while ((getchar()) != '\n');
    }
    novo->estado = (EstadoJogo)(op - 1);

    printf("Nota: ");
    while (scanf("%f", &novo->nota) != 1) {
        printf("Insira apenas numeros: ");
        while ((getchar()) != '\n');
    }
    while (getchar() != '\n');

    printf("Horas jogadas: ");
    while (scanf("%d", &novo->horasJogadas) != 1) {
        printf("Insira apenas numeros: ");
        while ((getchar()) != '\n');
    }
    
    printf("Desenvolvedora: ");
    scanf(" %[^\n]%*c", novo->Desenvolvedora);
    
    while (getchar() != '\n');

    novo->removido = 0;
    return novo;
}

void carregar_arquivo_arvore(tabela *tab, TipoArvore tipo) {
    FILE *arq;
    size_t len;
    char nome[16], *linha = (char*)malloc(len), delim[] = ";";

    switch (tipo) {
        case BST:
            strcpy(nome, "indicesbst.dat");
            break;
        case AVL:
            strcpy(nome, "indicesavl.dat");
            break;
        case RB:
            strcpy(nome, "indicesrb.dat");
            break;
    }

    arq = fopen(nome, "r+");
    if (arq != NULL) {
        while (getline(&linha, &len, arq) > 0) {
            char *ptr;
            ptr = strtok(linha, delim);
            int indice = atoi(ptr);
            ptr = strtok(NULL, delim);
            tirar_enter(ptr);

            switch (tipo) {
                case BST:
                    tab->indiceBst = adicionarBst(inicializarIndiceBst(indice, ptr), tab->indiceBst);
                    break;
                case AVL:
                    tab->indice_avl = adicionar_avl(tab->indice_avl, inicializar_indice_avl(indice, ptr));
                    break;
                case RB:
                    inserir_rb(&tab->indice_rb, inicializar_indice_rb(indice, ptr));
                    break;
            }
        }
        fclose(arq);
    }

    free(linha);
}

RegistroJogo buscar_jogo(FILE *arq, int indice) {
    RegistroJogo temp;
    if (indice >= 0) {
        if (arq != NULL) {
            long len = sizeof(char) * 256;
            char *buffer = (char *)malloc(len);
            char delim[] = ";";

            fseek(arq, indice, SEEK_SET);
            getline(&buffer, &len, arq);

            char *ptr = strtok(buffer, delim);
            temp.removido = atoi(ptr);

            ptr = strtok(NULL, delim);
            strcpy(temp.nome, ptr);

            ptr = strtok(NULL, delim);
            temp.dataLancamento = (char *)malloc(sizeof(ptr));
            strcpy(temp.dataLancamento, ptr);

            ptr = strtok(NULL, delim);
            temp.estado = (EstadoJogo)atoi(ptr);

            ptr = strtok(NULL, delim);
            temp.nota = atof(ptr);

            ptr = strtok(NULL, delim);
            temp.horasJogadas = atoi(ptr);

            return temp;
        }
        printf("Arquivo invalido!\n");
    } else
        printf("Indice invalido!\n");

    temp.removido = 1;
    return temp;
}

void imprimir_elemento(RegistroJogo jogo) {
    printf("Nome: %s\n", jogo.nome);
    printf("Data de Lançamento: %s\n", jogo.dataLancamento);
    printf("Estado: %s\n", estado_enum(jogo.estado));
    printf("Nota: %.2f\n", jogo.nota);
    printf("Horas jogadas: %d\n", jogo.horasJogadas);
    printf("Descricao: %s\n", jogo.descricao);
    printf("Desenvolvedora: %s\n", jogo.desenvolvedora);
    printf("\n");
}

void listar_por_nome(FILE *arq, bst raiz) {
    if (raiz != NULL) {
        listar_por_nome(arq, raiz->esq);
        printf("\n-----------------------------------------------\n\n");
        RegistroJogo jogo = buscar_jogo(arq, raiz->dado->indice);
        imprimir_elemento(jogo);
        listar_por_nome(arq, raiz->dir);
    }
}

void listar_por_data_lancamento(FILE *arq, avl raiz) {
    if (raiz != NULL) {
        listar_por_data_lancamento(arq, raiz->esq);
        printf("\n-----------------------------------------------\n\n");
        RegistroJogo jogo = buscar_jogo(arq, raiz->dado->indice);
        imprimir_elemento(jogo);
        listar_por_data_lancamento(arq, raiz->dir);
    }
}

void listar_por_desenvolvedora(FILE *arq, rb_tree *arvore_rb, char *desenvolvedora) {
    rb_node *no = buscar_por_desenvolvedora(arvore_rb, desenvolvedora);

    if (no != NULL) {
        listar_por_desenvolvedora_aux(arq, no, desenvolvedora);
    } else {
        printf("Nenhum jogo encontrado para a desenvolvedora: %s\n", desenvolvedora);
    }
}

void listar_por_desenvolvedora_aux(FILE *arq, rb_node *raiz, char *desenvolvedora) {
    if (raiz != NULL) {
        listar_por_desenvolvedora_aux(arq, raiz->left, desenvolvedora);

        if (strcmp(raiz->dado->desenvolvedora, desenvolvedora) == 0) {
            printf("\n-----------------------------------------------\n\n");
            RegistroJogo jogo = buscar_jogo(arq, raiz->dado->indice);
            imprimir_elemento(jogo);
        }

        listar_por_desenvolvedora_aux(arq, raiz->right, desenvolvedora);
    }
}

void salvar_arquivoBst(char *nome, bst a) {
	FILE *arq;
	arq = fopen(nome, "w+");
	if(arq != NULL) {
		salvar_auxiliarBst(a, arq);
		fclose(arq);
	}
}

void salvar_auxiliarBst(bst raiz, FILE *arq){
	if(raiz != NULL) {
		fprintf(arq, "%d;%s\n", raiz->dado->indice, raiz->dado->nome);
		salvar_auxiliarBst(raiz->esq, arq);
		salvar_auxiliarBst(raiz->dir, arq);
	}
}

void salvar_arquivo_avl(char *nome, avl raiz) {
	FILE *arq;
	arq = fopen(nome, "w+");
	if(arq != NULL) {
		salvar_auxiliar_avl(raiz, arq);
		fclose(arq);
	}
}

void salvar_auxiliar_avl(avl raiz, FILE *arq){
	if(raiz != NULL) {
		fprintf(arq, "%d;%d\n", raiz->dado->indice, raiz->dado->codigo);
		salvar_auxiliar_avl(raiz->esq, arq);
		salvar_auxiliar_avl(raiz->dir, arq);
	}

}

void salvar_arquivo_rb(char *nome, rb raiz) {
	FILE *arq;
	arq = fopen(nome, "w+");
	if(arq != NULL) {
		salvar_auxiliar_rb(raiz, arq);
		fclose(arq);
	}
}

void salvar_auxiliar_rb(rb raiz, FILE *arq){
	if(raiz != NULL) {
		fprintf(arq, "%d;%s\n", raiz->dado->indice, raiz->dado->descricao);
		salvar_auxiliar_rb(raiz->esq, arq);
		salvar_auxiliar_rb(raiz->dir, arq);
	}

}

void finalizar (tabela *tab) {
	fclose(tab->arquivo_dados);
	salvar_arquivoBst("indicesbst.dat", tab->indiceBst);
	salvar_arquivo_avl("indicesavl.dat", tab->indice_avl);
	salvar_arquivo_rb("indicesrb.dat", tab->indice_rb);
}



