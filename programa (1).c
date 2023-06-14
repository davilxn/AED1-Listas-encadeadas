#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <locale.h>
#include "listaDE.h"

typedef struct filme {
    int id;
    char titulo[maximo];
    int ano;
    float imdb;
    int metascore;
    int bilheteria;
} Filme;

int compTitulo(const void* elem1, const void* elem2) {
    const Filme* filme1 = (const Filme*)elem1;
    const Filme* filme2 = (const Filme*)elem2;
    int fator = strcmp(filme1->titulo, filme2->titulo);
    return fator;
}

int compMetascore(const void* elem1, const void* elem2) {
    const Filme* filme1 = (const Filme*)elem1;
    const Filme* filme2 = (const Filme*)elem2;
    int fator = filme1->metascore - filme2->metascore;
    return fator;
}

int compAno(const void* elem1, const void* elem2) {
    const Filme* filme1 = (const Filme*)elem1;
    const Filme* filme2 = (const Filme*)elem2;
    int fator = filme1->ano - filme2->ano;
    return fator;
}

int compBilheteria(const void* elem1, const void* elem2) {
    const Filme* filme1 = (const Filme*)elem1;
    const Filme* filme2 = (const Filme*)elem2;
    int fator = filme1->bilheteria - filme2->bilheteria;
    return fator;
}

int compIMDB(const void* elem1, const void* elem2) {
    const Filme* filme1 = (const Filme*)elem1;
    const Filme* filme2 = (const Filme*)elem2;
    int fator;
    if (filme1->imdb < filme2->imdb) {
        fator = -1;
    } else if (filme1->imdb > filme2->imdb) {
        fator = 1;
    } else {
        fator = 0;
    }
    return fator;
}

void criarFilme(Lista* li, int id) {
    Filme* filme = (Filme*)malloc(sizeof(Filme));

    filme->id = id;

    printf("Digite o título do filme: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]%*c", filme->titulo);

    printf("Digite o ano do filme: ");
    scanf("%d", &filme->ano);

    printf("Nota no IMDB: ");
    scanf("%f", &filme->imdb);

    printf("Nota no Metacritic: ");
    scanf("%d", &filme->metascore);

    printf("Bilheteria do filme: ");
    scanf("%d", &filme->bilheteria);

    inserirFim(li, filme);
}

void imprimirFilme(void* elemento) {
    Filme* filme = (Filme*)elemento;
    printf("\nId: %d    Titulo: %-45s    ano_lancamento: %d    metascore: %d    imdb: %.1f    bilheteira: %d", filme->id, filme->titulo, filme->ano, filme->metascore, filme->imdb,  filme->bilheteria);
}

No* buscarid(Lista* lista, int id) {
    No* noAtual = lista->comeco;

    while (noAtual != NULL) {
        Filme* filme = (Filme*)noAtual->info;
        if (filme->id == id) {
            return noAtual;
        }

        noAtual = noAtual->prox;
    }
    return NULL;
}

void remover_id(Lista *lista, int id, void (*liberarElemento)(void*)) {
    No* atual= lista->comeco;
    Filme *aux = (Filme*)malloc(sizeof(Filme));
    while (atual!= NULL) {
        aux = atual->info;
        if (aux->id == id) {
            No* ant = atual->ant;
            No* prox = atual->prox;
            if (ant != NULL)
                ant->prox = prox;
            else
                lista->comeco = prox;

            if (prox != NULL)
                prox->ant = ant;
            else
                lista->fim = ant;

            liberarElemento(atual);
            break;
        }
        atual = atual->prox;
    }
}

int main() {
    //setlocale(LC_ALL, "Portuguese");
    Lista* lista = criarLista();
    char *S[50];
    char *ptr;
    FILE *fptr;
    fptr = fopen("Copia_filmes_base3.csv", "r");
    int contId = 0;
    while(EOF != fscanf(fptr, "%[^\n]\n", S)){
        Filme* novo_filme = (Filme*)malloc(sizeof(Filme));
        novo_filme->id = contId;
        ptr = strtok(S, ",");
        int cont2 = 0;
        while (ptr != NULL){
                if (cont2 == 0){
                    strcpy(novo_filme->titulo, ptr);
                }else if(cont2 == 1){
                    novo_filme->ano = atoi(ptr);
                }else if (cont2 == 2){
                    novo_filme->imdb = atof(ptr);
                }else if (cont2 == 3){
                    novo_filme->metascore = atoi(ptr);
                }else if (cont2 == 4){
                    novo_filme->bilheteria = atoi(ptr);
                }
            ptr = strtok(NULL, ",");
            cont2++;
        }
        inserirFim(lista, novo_filme);
        contId++;
    }
    fclose(fptr);
    printf("Lista de Filmes (antes da ordenação):\n");
    imprimirLista(lista, imprimirFilme);

    quicksort(lista, compTitulo);

    int opcao;
    int id;
    No* aux;
    do {
        printf("\n---------------------------\n");
        printf("Escolha uma opção:\n");
        printf("1. Ordenar por título\n");
        printf("2. Ordenar por metascore\n");
        printf("3. Ordenar por IMDB\n");
        printf("4. Inserir filme\n");
        printf("5. Buscar filme por Id\n");
        printf("6. Remover filme por Id\n");
        printf("0. Sair\n");
        printf("---------------------------\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        printf("");

        switch (opcao) {
            case 1:
                quicksort(lista, compTitulo);
                printf("\n\nLista de Filmes (ordenada por título):\n");
                imprimirLista(lista, imprimirFilme);
                break;
            case 2:
                quicksort(lista, compMetascore);
                printf("\n\nLista de Filmes (ordenada por metascore):\n");
                imprimirLista(lista, imprimirFilme);
                break;
            case 3:
                quicksort(lista, compIMDB);
                printf("\n\nLista de Filmes (ordenada por IMDB):\n");
                imprimirLista(lista, imprimirFilme);
                break;
            case 4:
                criarFilme(lista, contId);
                imprimirLista(lista, imprimirFilme);
                contId++;
                break;
            case 5:
                printf("Id do filme procurado: ");
                scanf("%d", &id);
                aux = buscarid(lista, id);
                if (aux != NULL){
                    imprimirFilme(aux->info);
                }else{
                    printf("Id não localizado");
                }
                break;
            case 6:
                printf("Id do filme a ser excluido: ");
                scanf("%d", &id);
                remover_id(lista,id,liberarElemento);
                imprimirLista(lista, imprimirFilme);
                break;
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }

        printf("\n");
    } while (opcao != 0);

    destruirLista(lista, free);

    return 0;
}
