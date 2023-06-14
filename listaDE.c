#include <stdio.h>
#include <stdlib.h>
#include "listaDE.h"

typedef struct no {
    void* info;
    struct no* ant;
    struct no* prox;
} No;

typedef struct lista {
    No* comeco;
    No* fim;
    int qtd;
} Lista;

void liberarElemento(No *no){
    free(no->info);
    free(no);
}

Lista* criarLista() {
    Lista* lista = (Lista*)malloc(sizeof(Lista));
    lista->comeco = NULL;
    lista->fim = NULL;
    lista->qtd = 0;
    return lista;
}

void destruirLista(Lista* lista, void (*liberarElemento)(void*)) {
    No* atual = lista->comeco;
    while (atual != NULL) {
        No* prox = atual->prox;
        liberarElemento(atual->info);
        free(atual);
        atual = prox;
    }
    free(lista);
}

int qtdLista(Lista* lista) {
    if (lista->qtd == 0) {
    	return 0;
	} else {
		return lista->qtd;
	}
}

int listaVazia(Lista* lista) {
    if (lista->qtd == 0) {
    	return 1;
	} else {
		return 0;
	}
}

No* criarNo(void* elemento) {
    No* no = (No*)malloc(sizeof(No));
    no->info = elemento;
    no->ant = NULL;
    no->prox = NULL;
    return no;
}

void inserirInicio(Lista* lista, void* elemento) {
    No* novoNo = criarNo(elemento);
    if (lista->comeco == NULL) {
        lista->comeco = novoNo;
        lista->fim = novoNo;
    } else {
        novoNo->prox = lista->comeco;
        lista->comeco->ant = novoNo;
        lista->comeco = novoNo;
    }
    lista->qtd++;
}

void inserirFim(Lista* lista, void* elemento) {
    No* novoNo = criarNo(elemento);
    if (lista->fim == NULL) {
        lista->comeco = novoNo;
        lista->fim = novoNo;
    } else {
        novoNo->ant = lista->fim;
        lista->fim->prox = novoNo;
        lista->fim = novoNo;
    }
    lista->qtd++;
}

void inserirPosicao(Lista* lista, void* elemento, int posicao) {
    if (posicao < 0 || posicao > lista->qtd) {
        printf("Posição inválida!\n");
        return;
    }
    if (posicao == 0) {
        inserirInicio(lista, elemento);
        return;
    }
    if (posicao == lista->qtd) {
        inserirFim(lista, elemento);
        return;
    }
    No* novoNo = criarNo(elemento);
    No* atual = lista->comeco;
    int indice = 0;
    while (indice < posicao) {
        atual = atual->prox;
        indice++;
    }
    No* ant = atual->ant;
    novoNo->ant = ant;
    novoNo->prox = atual;
    ant->prox = novoNo;
    atual->ant = novoNo;
    lista->qtd++;
}

void removerPosicao(Lista* lista, int posicao, void (*liberarElemento)(void*)) {
    if (posicao < 0 || posicao >= lista->qtd) {
        printf("Posição inválida!\n");
        return;
    }
    if (posicao == 0) {
        No* noRemovido = lista->comeco;
        lista->comeco = noRemovido->prox;
        if (lista->comeco != NULL) {
            lista->comeco->ant = NULL;
        } else {
            lista->fim = NULL;
        }
        liberarElemento(noRemovido->info);
        free(noRemovido);
        lista->qtd--;
        return;
    }
    if (posicao == lista->qtd - 1) {
        No* noRemovido = lista->fim;
        lista->fim = noRemovido->ant;
        lista->fim->prox = NULL;
        liberarElemento(noRemovido->info);
        free(noRemovido);
        lista->qtd--;
        return;
    }
    No* atual = lista->comeco;
    int indice = 0;
    while (indice < posicao) {
        atual = atual->prox;
        indice++;
    }
    No* ant = atual->ant;
    No* prox = atual->prox;
    ant->prox = prox;
    prox->ant = ant;
    liberarElemento(atual->info);
    free(atual);
    lista->qtd--;
}

void imprimirLista(Lista* lista, void (*imprimirElemento)(void*)) {
    No* atual = lista->comeco;
    while (atual != NULL) {
        imprimirElemento(atual->info);
        atual = atual->prox;
    }
    printf("\n");
}

void trocarElementos(No* no1, No* no2) {
    void* temp = no1->info;
    no1->info = no2->info;
    no2->info = temp;
}

No* particionar(Lista* lista, No* inicio, No* fim, int (*compararElementos)(const void*, const void*)) {
    void* pivo = fim->info;
    No* i = inicio->ant;

    for (No* j = inicio; j != fim; j = j->prox) {
        if (compararElementos(j->info, pivo) <= 0) {
            i = (i == NULL) ? inicio : i->prox;
            trocarElementos(i, j);
        }
    }

    i = (i == NULL) ? inicio : i->prox;
    trocarElementos(i, fim);

    return i;
}

void quicksortRecursivo(Lista* lista, No* inicio, No* fim, int (*compararElementos)(const void*, const void*)) {
    if (inicio != NULL && fim != NULL && inicio != fim && inicio != fim->prox) {
        No* pivo = particionar(lista, inicio, fim, compararElementos);
        quicksortRecursivo(lista, inicio, pivo->ant, compararElementos);
        quicksortRecursivo(lista, pivo->prox, fim, compararElementos);
    }
}

void quicksort(Lista* lista, int (*compararElementos)(const void*, const void*)) {
    quicksortRecursivo(lista, lista->comeco, lista->fim, compararElementos);
}

