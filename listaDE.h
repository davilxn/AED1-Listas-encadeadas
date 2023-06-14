#ifndef listaDE_h
#define listaDE_h
#define maximo 100

#include "listaDE.c"

typedef struct no No;

typedef struct lista Lista;

Lista* criarLista();
int qtdLista(Lista* lista);
int listaVazia(Lista* lista);
void liberarElemento(No *no);
void destruirLista(Lista* lista, void (*liberarElemento)(void*));
void inserirInicio(Lista* lista, void* elemento);
void inserirFim(Lista* lista, void* elemento);
void inserirPosicao(Lista* lista, void* elemento, int posicao);
void removerPosicao(Lista* lista, int posicao, void (*liberarElemento)(void*));
void imprimirLista(Lista* lista, void (*imprimirElemento)(void*));
void quicksort(Lista* lista, int (*compararElementos)(const void*, const void*));

#endif

