#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAM 20

typedef struct tipoVertice
{
    char nome[30];
    int distancia;
    struct tipoVertice *prox;
}TVertice;


typedef struct tipoLista
{
    int distancia;
    TVertice *inicio;
    TVertice *fim;
}TLista;

// Declarando as Funcoes
int menu();

// Funcoes para inicializar
void inicializarMatriz(int matriz[TAM][TAM]);
void inicializaVetor(TLista *vetor);
void inicializaLista(TLista *lista);

// Funcoes para exibir
void imprimirMatriz(int matriz[TAM][TAM]);
void imprimirVertices(TLista *vetor);
void exibir_lista(TLista *lista);
void exibir_vetor(TLista *vetor);

// Funcoes para inserir as cidades
void inserirNomeCidades(TLista *lista, char *nomeCidade, int distancia);
void inserirRelacoesMatriz(int matriz[TAM][TAM], TLista *vetor, char *nomeCidade1, char *nomeCidade2, int distancia);
void inserirCidadesLista(TLista *vetor, int matriz[TAM][TAM]);

void distancia(TLista *vetorCidades, TLista *listaCidadesInseridas, char *nomeCidade);
void imprimirCidadesDistancia(TLista *listaCidades);
int encontrarPosicaoCidade(TLista *vetorCidades, char *nomeCidade);

