#include "rb.h"
#include <stdio.h>
#include <stdlib.h>

rb no_null;

indice_rb* inicializar_indice_rb(int indice, char *desenvolvedora)  {
	indice_rb *novo = (indice_rb*) malloc(sizeof(indice_rb));
	novo->indice = indice;
	novo->desenvolvedora = (char*) malloc(sizeof(char));
	strcpy(novo->desenvolvedora, desenvolvedora);
	return novo;
}

void inicializar_rb(rb *raiz) {
	*raiz = NULL;
	no_null = (rb) malloc(sizeof(struct no_rb));
	no_null->cor = DUPLO_PRETO;
	no_null->dado = 0;
	no_null->esq = NULL;
	no_null->dir = NULL;
}

int eh_raiz_rb(rb elemento) {
	return (elemento->pai == NULL);
}

int eh_filho_esquerdo_rb(rb elemento) {
	return (elemento->pai != NULL && elemento == elemento->pai->esq);
}
int eh_filho_direito_rb(rb elemento) {
	return (elemento->pai != NULL && elemento == elemento->pai->dir);
}

rb eh_irmao_rb(rb elemento) {

	if(eh_filho_esquerdo_rb(elemento))
		return elemento->pai->dir;
	else
		return elemento->pai->esq;
}

rb tio_rb(rb elemento) {
	return eh_irmao_rb(elemento->pai);
}


enum cor cor_rb(rb elemento) {
	enum cor c;
	if(elemento == NULL)
		c = PRETO;
	else
		c = elemento->cor;
	return c;
}
	
int altura_rb(rb a) {
	if(a == NULL) 
		return 0;
	else {
		int esq, dir;
		esq = altura_rb(a->esq);
		dir = altura_rb(a->dir);

		if(esq > dir)
			return (esq + 1);
		else
			return (dir + 1);
	}
}

indice_rb* maior_elemento_rb(rb raiz) {
	if(raiz == NULL)
		return NULL;
	if(raiz->dir == NULL)
		return raiz->dado;
	else
		return maior_elemento_rb(raiz->dir);
}

void imprimir_rb(rb raiz) {
	if(raiz != NULL) {
		imprimir_rb(raiz->esq);
		imprimir_elemento_rb(raiz);
		imprimir_rb(raiz->dir);
	}
}

void imprimir_elemento_rb(rb raiz) {
	switch(raiz->cor) {
		case PRETO:
			printf("\x1b[30m[%s]\x1b[0m", raiz->dado->desenvolvedora);
			break;
		case VERMELHO:
			printf("\x1b[31m[%s]\x1b[0m", raiz->dado->desenvolvedora);
			break;
		case DUPLO_PRETO:
			printf("\x1b[32m[%s]\x1b[0m", raiz->dado->desenvolvedora);
			break;
	}
}


void inserir_rb(rb *raiz, indice_rb *valor) {
	rb aux, pai, novo;
	aux = *raiz; 
	pai = NULL;

	while(aux != NULL) {
		pai = aux;

		if(strcmp(aux->dado->desenvolvedora, valor->desenvolvedora) >= 0)
			aux = aux->esq;
		else
			aux = aux->dir;
	}

	novo = (rb) malloc(sizeof(struct no_rb));
	novo->dado = valor;
	novo->esq = NULL;
	novo->dir = NULL;
	novo->pai = pai;
	novo->cor = VERMELHO;

	if(eh_raiz_rb(novo)) {
		*raiz = novo;
	} else {
		if(strcmp(valor->desenvolvedora, pai->dado->desenvolvedora) > 0)
			pai->dir = novo;
		else  
			pai->esq = novo; 
	}

	ajustar_rb(raiz, novo);

}

void remover_rb(rb *raiz, rb* raiz_relativa, char* desenvolvedora) {
	rb aux = *raiz_relativa;

	while(aux != NULL) {
		if(strcmp(desenvolvedora, aux->dado->desenvolvedora) == 0) {

			if(aux->esq == NULL && aux->dir == NULL) {
	
				if(eh_raiz_rb(aux)) {
					*raiz = NULL;
					break;
				}

				if(aux->cor == VERMELHO) {
					if(eh_filho_esquerdo_rb(aux))
						aux->pai->esq = NULL;
					else
						aux->pai->dir = NULL;
					break;

				} else {

					no_null->pai = aux->pai;

					if(eh_filho_esquerdo_rb(aux))
						aux->pai->esq = no_null;
					else 
						aux->pai->dir = no_null;

					reajustar_rb(raiz, no_null);
					break;
				}
			}

			if(aux->dir == NULL) {
				aux->esq->cor = PRETO;
				if(eh_raiz_rb(aux)) {
					*raiz = aux->esq;
				} else {
					if(eh_filho_esquerdo_rb(aux))
						aux->pai->esq = aux->esq;
					else 
						aux->pai->dir = aux->esq;
				}
				break;
			}

			if(aux->esq == NULL) {
				aux->dir->cor = PRETO;
				if(eh_raiz_rb(aux)) {
					*raiz = aux->dir;
				} else {
					if(eh_filho_esquerdo_rb(aux))
						aux->pai->esq = aux->dir;
					else
						aux->pai->dir = aux->dir;
				}
				break;
			}

			if(aux->dir != NULL && aux->esq != NULL) {
				aux->dado = maior_elemento_rb(aux->esq);
				remover_rb(raiz, &(aux->esq), aux->dado->desenvolvedora);
				break;
			}

		} else {
			if(strcmp(desenvolvedora, aux->dado->desenvolvedora) > 0)
				aux = aux->dir;
			else
				aux = aux->esq;
		}
	}
}

void reajustar_rb(rb *raiz, rb elemento) {
	
	if(eh_raiz_rb(elemento)) {
		elemento->cor = PRETO;

		return;
	}

	if(cor_rb(elemento->pai) == PRETO &&
	 cor_rb(eh_irmao_rb(elemento)) == VERMELHO &&
	 (cor_rb(eh_irmao_rb(elemento)->dir) == PRETO || eh_irmao_rb(elemento)->dir == NULL) &&
	 (cor_rb(eh_irmao_rb(elemento)->esq) == PRETO || eh_irmao_rb(elemento)->esq == NULL)) {
		if(eh_filho_esquerdo_rb(elemento))
			rotacao_simples_esquerda_rb(raiz, elemento);
		else 
			rotacao_simples_direita_rb(raiz, elemento);

		elemento->pai->pai->cor = PRETO;
		elemento->pai->cor = VERMELHO;

		return;
	 }

	 if(cor_rb(elemento -> pai) == PRETO && cor_rb(eh_irmao_rb(elemento)) == PRETO &&
		(cor_rb(eh_irmao_rb(elemento)-> dir)  == PRETO || eh_irmao_rb(elemento) -> dir == NULL) && 
		(cor_rb(eh_irmao_rb(elemento) -> esq)  == PRETO || eh_irmao_rb(elemento) -> esq == NULL)){	
		eh_irmao_rb(elemento) -> cor = VERMELHO;
		retira_duplo_preto_rb(raiz, elemento);
		reajustar_rb(raiz, elemento->pai);

		return;
	}

	if(cor_rb(elemento -> pai) == VERMELHO && 
		(cor_rb(eh_irmao_rb(elemento)) == PRETO || eh_irmao_rb(elemento) == NULL) &&
		(cor_rb(eh_irmao_rb(elemento)-> dir)  == PRETO || eh_irmao_rb(elemento) -> dir == NULL) && (cor_rb(eh_irmao_rb(elemento) -> esq) == PRETO || eh_irmao_rb(elemento) -> esq == NULL)){

			elemento -> pai -> cor = PRETO;
			eh_irmao_rb(elemento) -> cor = VERMELHO;
			
			retira_duplo_preto_rb(raiz, elemento); 

			return;

	}

	if(eh_filho_esquerdo_rb(elemento) && cor_rb(eh_irmao_rb(elemento)) == PRETO &&
		(cor_rb(eh_irmao_rb(elemento) -> dir) == PRETO || eh_irmao_rb(elemento) -> dir == NULL) && cor_rb(eh_irmao_rb(elemento) -> esq) == VERMELHO){
			
			rotacao_simples_direita_rb(raiz, eh_irmao_rb(elemento));
			eh_irmao_rb(elemento) -> cor = PRETO;
			eh_irmao_rb(elemento) -> dir -> cor = VERMELHO;
			
			reajustar_rb(raiz, elemento);

			return;
		}

	if(eh_filho_direito_rb(elemento) && cor_rb(eh_irmao_rb(elemento)) == PRETO &&
		(cor_rb(eh_irmao_rb(elemento) -> esq) == PRETO || eh_irmao_rb(elemento) -> esq == NULL) 		
		&& cor_rb(eh_irmao_rb(elemento) -> dir) == VERMELHO) {
		
			rotacao_simples_esquerda_rb(raiz, eh_irmao_rb(elemento));
			eh_irmao_rb(elemento) -> cor = PRETO;
			eh_irmao_rb(elemento) -> esq -> cor = VERMELHO;
			
			reajustar_rb(raiz, elemento);

			return;
	}

	if(eh_filho_esquerdo_rb(elemento) && 
		cor_rb(eh_irmao_rb(elemento)) == PRETO && 
		cor_rb(eh_irmao_rb(elemento) -> dir) == VERMELHO) {
		
		enum cor cor_original_pai = cor_rb(elemento -> pai);
		
		rotacao_simples_esquerda_rb(raiz, elemento -> pai);
		
		elemento -> pai -> pai -> cor = cor_original_pai;
		elemento -> pai -> cor = PRETO;
		tio_rb(elemento) -> cor = PRETO;		
		
		retira_duplo_preto_rb(raiz, elemento);

		return;
	}

	//caso 6b
	if(eh_filho_direito_rb(elemento) && 
		cor_rb(eh_irmao_rb(elemento)) == PRETO && 
		cor_rb(eh_irmao_rb(elemento) -> esq) == VERMELHO) {

		enum cor cor_original_pai = cor_rb(elemento -> pai);
		
		rotacao_simples_direita_rb(raiz, elemento -> pai);
		
		elemento -> pai -> pai -> cor = cor_original_pai;
		elemento -> pai -> cor = PRETO;
		tio_rb(elemento) -> cor = PRETO;		
		
		retira_duplo_preto_rb(raiz, elemento);

		return;
	}
}

void retira_duplo_preto_rb(rb *raiz, rb elemento) {
	if(elemento == no_null) {
		if(eh_filho_esquerdo_rb(elemento))
			elemento->pai->esq = NULL;
		else
			elemento->pai->dir = NULL;
	} else {
		elemento->cor = PRETO;
	}
}


void ajustar_rb(rb* raiz, rb novo) {
	
	while(cor_rb(novo->pai) == VERMELHO && cor_rb(novo) == VERMELHO) {

		if(cor_rb(tio_rb(novo)) == VERMELHO){

			tio_rb(novo)->cor = PRETO;
			novo->pai->cor = PRETO;
			novo->pai->pai->cor = VERMELHO;

			novo = novo->pai->pai;

			continue;
		}
		if(eh_filho_esquerdo_rb(novo) && eh_filho_esquerdo_rb(novo->pai)) {
		
			rotacao_simples_direita_rb(raiz, novo->pai->pai);
			novo->pai->cor = PRETO;
			novo->pai->dir->cor = VERMELHO;

			continue;
		}
	
		if(eh_filho_direito_rb(novo) && eh_filho_direito_rb(novo->pai)) {
			rotacao_simples_esquerda_rb(raiz, novo->pai->pai);
			novo->pai->cor = PRETO;
			novo->pai->esq->cor = VERMELHO;

			continue;
		}
	
		if(eh_filho_direito_rb(novo) && eh_filho_esquerdo_rb(novo->pai)) {
			rotacao_simples_esquerda_rb(raiz, novo->pai);
			rotacao_simples_direita_rb(raiz, novo->pai);
			novo->dir->cor = VERMELHO;
			novo->esq->cor = VERMELHO;
			novo->cor = PRETO;

			continue;
		}
	
		if(eh_filho_esquerdo_rb(novo) && eh_filho_direito_rb(novo->pai)) {
            rotacao_simples_direita_rb(raiz, novo->pai);
            rotacao_simples_esquerda_rb(raiz, novo->pai);
            novo->dir->cor = VERMELHO;
            novo->esq->cor = VERMELHO;
            novo->cor = PRETO;
            
            continue;

		}
	}

	(*raiz)->cor = PRETO;
}



void rotacao_simples_direita_rb(rb *raiz, rb pivo) {
	rb p, u, t2;
	p = pivo;
	u = pivo->esq;
	t2 = u->dir;

	int posicao_pivo_esq = eh_filho_esquerdo_rb(pivo);

	p->esq = t2;

	if(t2 != NULL) 
		t2->pai = pivo;

	u->dir = pivo;
	u->pai = p->pai;
	p->pai = u;

	p->cor = VERMELHO;
	u->cor = PRETO;


	if(eh_raiz_rb(u))
		*raiz = u;

	else {
		if(posicao_pivo_esq)
			u->pai->esq = u;
		else
			u->pai->dir = u;
	}
}

void rotacao_simples_esquerda_rb(rb *raiz, rb pivo) {
	rb p, u, t2;
	p = pivo;
	u = p->dir;
	t2 = u->esq;

	int posicao_pivo_dir = eh_filho_direito_rb(pivo);

	p->dir = t2;

	if(t2 != NULL)
		t2->pai = p;

	u->esq = p;
	u->pai = p->pai;
	p->pai = u;

	p->cor = VERMELHO;
	u->cor = PRETO;
	
	if(eh_raiz_rb(u))
		*raiz = u;
	else {
		if(posicao_pivo_dir)
			u->pai->dir = u;
		else
			u->pai->esq = u;
	}
}

void preorder_rb (rb raiz) {
  if (raiz != NULL) {
      imprimir_elemento_rb(raiz);
      preorder_rb (raiz->esq);
      preorder_rb (raiz->dir);
    }
}

int buscar_indice_rb(rb raiz, char* desenvolvedora) {
	if(desenvolvedora != NULL && raiz != NULL) {
		int cmp = strcmp(desenvolvedora, raiz->dado->desenvolvedora);
		if(cmp == 0) {
			return raiz->dado->indice;
		}
		else {
			if(cmp > 0)
				return buscar_indice_rb(raiz->dir, desenvolvedora);
			else 
				return buscar_indice_rb(raiz->esq, desenvolvedora);
		}
	} else {
		return -1;
	}
}