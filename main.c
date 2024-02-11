#include <stdio.h>
#include <stdlib.h>
#include "tabela/tabela.h"
#include "arvores/bst.h"
#include "arvores/avl.h"
#include "arvores/rb.h"

int op_menu;

int menu();
int menu_buscar();
int menu_listar();
int menu_remover();
int voltar();
void limpar_tela();

int main() {
    tabela tab;
    char nome[50], *descricao = (char *)malloc(sizeof(char) * 256);

    if (inicializarTabela(&tab)) {
        do {
            switch (menu()) {
                case 1:
                    printf("Insira os dados do Jogo\n\n");
                    if (inserir_jogo(&tab, ler_dados()))
                        printf("Sucesso ao inserir!\n");
                    else
                        printf("Jogo não inserido\n");
                    voltar();
                    break;

                case 2:
                    while (1) {
                        switch (menu_buscar()) {
                            case 1:
                                printf("Buscar Jogo por nome\n\n");
                                printf("Nome: ");
                                fgets(nome, sizeof(nome), stdin);
                                tirar_enter(nome);
                                limpar_tela();
                                buscar_e_imprimir_por_nome(&tab, nome);
                                break;

                            case 2:
                                printf("Buscar Jogo por código\n\n");
                                printf("Código: ");
                                int codigo;
                                scanf("%d", &codigo);
                                limpar_tela();
                                buscar_e_imprimir_por_codigo(&tab, codigo);
                                break;

                            case 3:
                                printf("Buscar Jogo por descrição\n\n");
                                printf("Descrição: ");
                                fgets(descricao, 255, stdin);
                                tirar_enter(descricao);
                                limpar_tela();
                                buscar_e_imprimir_por_descricao(&tab, descricao);
                                break;

                            case 4:
                                goto fim_buscar;
                                break;

                            default:
                                printf("Opção inválida!\n");
                                break;
                        }
                        voltar();
                    }
                fim_buscar:;
                    break;

                case 3:
                    while (1) {
                        switch (menu_listar()) {
                            case 1:
                                printf("Listando Jogos por nome\n\n");
                                listar_por_nome(tab.arquivo_dados, tab.indiceBst);
                                break;

                            case 2:
                                printf("Listando Jogos por código\n\n");
                                listar_por_codigo(tab.arquivo_dados, tab.indice_avl);
                                break;

                            case 3:
                                printf("Listando Jogos por descrição\n\n");
                                listar_por_descricao(tab.arquivo_dados, tab.indice_rb);
                                break;

                            case 4:
                                goto fim_listar;
                                break;

                            default:
                                break;
                        }
                        voltar();
                    }
                fim_listar:;
                    break;

                case 4:
                    while (1) {
                        switch (menu_remover()) {
                            case 1:
                                printf("Remover por nome: ");
                                fgets(nome, sizeof(nome), stdin);
                                tirar_enter(nome);
                                remover_por_nome(&tab, nome);
                                break;

                            case 2:
                                printf("Remover por código: ");
                                int codigo;
                                scanf("%d", &codigo);
                                remover_por_codigo(&tab, codigo);
                                break;

                            case 3:
                                printf("Remover por descrição: ");
                                fgets(descricao, 255, stdin);
                                tirar_enter(descricao);
                                remover_por_descricao(&tab, descricao);
                                break;

                            case 4:
                                goto fim_remover;
                                break;

                            default:
                                printf("Opção inválida\n");
                                break;
                        }
                        voltar();
                    }
                fim_remover:;
                    break;

                case 5:
                    finalizar(&tab);
                    exit(1);
                    break;

                default:
                    printf("Opção inválida\n");
            }

        } while (1);
    }
    return 0;
}
