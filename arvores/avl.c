#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int altura_avl(avl a) {
	if(a == NULL) {
		return 0;
	} else {
		int esq = altura_avl(a->esq);
		int dir = altura_avl(a->dir);
	
		if(esq > dir)
			return esq + 1;
		else 
			return dir + 1;
		
	}
}

int comparar_datas(char *data1, char *data2) {
    return strcmp(data1, data2);
}

indice_avl *inicializar_indice_avl(char *data_lancamento, int indice) {
    indice_avl *novo = (indice_avl *)malloc(sizeof(indice_avl));
    strcpy(novo->data_lancamento, data_lancamento);
    novo->indice = indice;
    return novo;
}

int buscar_indice_avl(avl raiz, char *data_lancamento) {
    if (raiz != NULL) {
        int comparacao = comparar_datas(data_lancamento, raiz->dado->data_lancamento);
        if (comparacao == 0) {
            return raiz->dado->indice;
        } else if (comparacao < 0) {
            return buscar_indice_avl(raiz->esq, data_lancamento);
        } else {
            return buscar_indice_avl(raiz->dir, data_lancamento);
        }
    } else {
        return -1;
    }
}


avl adicionar_avl(avl a, indice_avl *v, int *cresceu) {
    if (cresceu == NULL) {
        int c = 1;
        cresceu = &c;
    }

    if (a == NULL) {
        avl new = (avl)malloc(sizeof(no_avl));
        new->dado = v;
        new->esq = NULL;
        new->dir = NULL;
        new->fb = 0;
        *cresceu = 1;
        return new;
    } else {
        int comparacao = comparar_datas(v->data_lancamento, a->dado->data_lancamento);

        if (comparacao == 0) {
            // Datas iguais, você pode decidir o que fazer nesse caso
            *cresceu = 0;
            return a;
        } else if (comparacao < 0) {
            a->esq = adicionar_avl(a->esq, v, cresceu);
        } else {
            a->dir = adicionar_avl(a->dir, v, cresceu);
        }

        if (*cresceu) {
            switch (a->fb) {
                case 0:
                    a->fb = (comparacao < 0) ? -1 : 1;
                    *cresceu = 1;
                    break;
                case -1:
                    if (comparacao < 0) {
                        a->fb = 0;
                        *cresceu = 0;
                    } else {
                        a->fb = 1;
                        *cresceu = 1;
                        a = rotacao_avl(a);
                    }
                    break;
                case 1:
                    if (comparacao > 0) {
                        a->fb = 0;
                        *cresceu = 0;
                    } else {
                        a->fb = -1;
                        *cresceu = 1;
                        a = rotacao_avl(a);
                    }
                    break;
            }
        }

        return a;
    }
}

avl remover_elemento_avl(avl a, char *data_lancamento, int *diminuiu) {
    if (a == NULL) {
        *diminuiu = 0;
        return a;
    }

    if (diminuiu == NULL) {
        int d = 0;
        diminuiu = &d;
    }

    int comparacao = comparar_datas(data_lancamento, a->dado->data_lancamento);

    if (comparacao == 0) {
        // Encontrou o nó a ser removido
        if (a->esq == NULL && a->dir == NULL) {
            free(a);
            *diminuiu = 1;
            return NULL;
        } else if (a->esq != NULL && a->dir != NULL) {
            // Nó com dois filhos
            avl aux = a->esq;

            // Procura o sucessor para substituir o valor a ser removido
            while (aux->dir != NULL)
                aux = aux->dir;

            a->dado = aux->dado;

            a->esq = remover_elemento_avl(a->esq, aux->dado->data_lancamento, diminuiu);

            switch (a->fb) {
                case 0:
                    a->fb = 1;
                    *diminuiu = 0;
                    break;
                case -1:
                    a->fb = 0;
                    *diminuiu = 1;
                    break;
                case 1:
                    *diminuiu = 1;
                    a = rotacao_avl(a);
            }
            return a;
        } else {
            // Nó com um filho
            avl aux;
            *diminuiu = 1;
            if (a->dir != NULL && a->esq == NULL) {
                aux = a->dir;
            } else {
                aux = a->esq;
            }
            free(a);
            return aux;
        }
    } else if (comparacao < 0) {
        a->esq = remover_elemento_avl(a->esq, data_lancamento, diminuiu);
    } else {
        a->dir = remover_elemento_avl(a->dir, data_lancamento, diminuiu);
    }

    if (*diminuiu) {
        switch (a->fb) {
            case -1:
                if (a->dir->fb == 0) {
                    *diminuiu = 0;
                } else {
                    *diminuiu = 1;
                }
                a->fb = -2;
                a = rotacao_avl(a);
                break;
            case 0:
                a->fb = -1;
                *diminuiu = 1;
                break;
            case 1:
                if (a->esq->fb == 0) {
                    *diminuiu = 0;
                } else {
                    *diminuiu = 1;
                }
                a->fb = -2;
                a = rotacao_avl(a);
                break;
        }
    }

    return a;
}

avl rotacao_avl(avl a){
    if (a->fb > 0){
        if(a->dir->fb >= 0){
            return rotacao_simples_esquerda_avl(a);
        }else{
            return rotacao_dupla_esquerda_avl(a);
        }
    }else{
        if (a->esq->fb <= 0){
            return rotacao_simples_direita_avl(a);
        }else{
            return rotacao_dupla_direita_avl(a);
        }

    }
}

avl rotacao_simples_esquerda_avl(avl a) {
	//quem ta desbalanceado eh p
	// fb(p) == 2, fb(u) == 1
	avl p, u;
	p = a;
	u = p->dir;

	//corrigindo fatores de balanco
	u->fb = 0;
	p->fb = 0;

	//rotacao_avl
	p->dir = u->esq;
	u->esq = p;

	return u;
}

avl rotacao_simples_direita_avl(avl a) {
	//fb(p) == -2, fb(u) == -1
	avl p, u;

	p = a;
	u = p->esq;

	//corrigindo fatores de balanco
	u->fb = 0;
	p->fb = 0;
	
	//rotação
	p->esq = u->dir;
	u->dir = p;

	return u;
}


avl rotacao_dupla_esquerda_avl(avl a){
 	//fb(p) = 2, fb(u) = -1
    avl p, u, v;

    p = a;
    u = p->dir;
    v = u->esq;

    //Rotação direita
    u->esq = v->dir;
    v->dir = u;
    p->dir = v;

    //Rotção esquerda
    p->dir = v->esq;
    v->esq = p;
    
    //Atualizando os fatores de balanço
    if(v->fb==0){  
        u->fb = 0;
        v->fb = 0;
        p->fb=0;
    
    }    
    else if(v->fb==-1){  

        u->fb = 1;
        v->fb = 0;
        p->fb = 0;
    }   
     else{  
        u->fb = 0;
        v->fb = 0;
        p->fb =-1;
    }
   return v;
}


avl rotacao_dupla_direita_avl(avl a) {
	avl p, u, v;

	p = a;
	u = p->esq;
   v = u->dir;

    // Rotação à esquerda    
    u->dir = v->esq;
    v->esq = u;
    p->esq = v;
    
    //Rotação á direita
    p->esq=v->dir;
    v->dir = p;
    
    //Atualizando os fatores de balanço
    if(v->fb == 0){ 

        u->fb = 0;
        p->fb = 0;
        v->fb = 0;
    }
    else if(v->fb==-1){

        u->fb = 0;
        v->fb = 0;
        p->fb = 1;

    }
    else {

        u->fb = -1;
        v->fb = 0;
        p->fb = 0;

    }
    return v;
}

void pre_order_avl(avl raiz) {
	if(raiz != NULL) {
		imprimir_elemento_avl(raiz);
		pre_order_avl(raiz->esq);
		pre_order_avl(raiz->dir);
	}
}

void pos_order_avl(avl raiz) {
	if(raiz != NULL) {
		pos_order_avl(raiz->esq);
		pos_order_avl(raiz->dir);
		imprimir_elemento_avl(raiz);
	}
}

void in_order_avl(avl raiz) {
	if(raiz != NULL) {
		in_order_avl(raiz->esq);
		imprimir_elemento_avl(raiz);
		in_order_avl(raiz->dir);
	}
}

void imprimir_elemento_avl(avl raiz) {
	if(raiz != NULL) {
		printf("%d | ", raiz->dado->codigo);

	}
}