#include "lista.h"

// Criacao do MENU
int menu()
{

    int opcao;

    system("CLS");

    printf("\n\n\n\t| MENU |\n\n");
    printf("1 - Imprimir Matriz.\n");
    printf("2 - Imprimir Relacoes.\n");
    printf("3 - Imprimir Cidades.\n");
    printf("4 - Calcular Menor Distancia.\n");
    printf("Informe uma opcao: ");
    scanf("%d", &opcao);

    return opcao;

}

/* ================================================================= */
void inicializarMatriz(int matriz[TAM][TAM])
{

    // Inicializar todas as posicoes da matriz com -1, ou seja, eh permitido distancias 0
    int i, j;
    for(i = 0; i < TAM; i++){
        for(j = 0; j < TAM; j++){

            matriz[i][j] = -1;

        }
    }

}

/* ================================================================= */
void inicializaLista(TLista *lista)
{

    // Inicializa a lista definido NULL para o inicio e o fim e distancia 0
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->distancia = 0;

}

/* ================================================================= */
void inicializaVetor(TLista *vetor)
{

    // Inicializa todas a posicoes do vetor que são do tipo TLista
    int i;
    for(i = 0; i < TAM; i++){
        inicializaLista(&vetor[i]);
    }

}

/* ================================================================= */
void imprimirMatriz(int matriz[TAM][TAM])
{
    // Imprimi as linhas e colunas da Matriz (Apenas ilustrativa)
    int i, j;
    printf("\n\n");

    for(i = 0; i < TAM; i++){
        for(j = 0; j < TAM; j++){

            printf("%d  ", matriz[i][j]);

        }
        printf("\n");
    }

    printf("\n\n");

}

/* ================================================================= */
void inserirNomeCidades(TLista *lista, char *nomeCidade, int distancia)
{

    // Alocar espaco para a insercao de um novo elemento
    TVertice *novo = (TVertice *) malloc (sizeof(TVertice));

    // Atribui os valores do novo elemento que sera inserido
    strcpy(novo->nome, nomeCidade);
    novo->distancia = distancia;
    novo->prox = NULL;

    // Se a lista for vazia insere o elemento no comeco da lista
    if (lista->inicio == NULL){
        lista->inicio = novo;

    } else {

        // Se nao inserir no comeco, o novo elemento sera inserido no final da lista
        TVertice *aux = lista->inicio;
        while (aux->prox != NULL)
        {
            aux = aux->prox;
        }
        aux->prox = novo;

    }

}

int encontrarPosicaoCidade(TLista *vetorCidades, char *nomeCidade)
{

    int i;

    // Percorrer todas as posicoes do vetor de lista
    for(i = 0; i < TAM; i++)
    {
        if(strcmp(vetorCidades[i].inicio->nome, nomeCidade) == 0){
            // Se encontrar o nome da cidade, retorna a posicao no vetor que a cidade esta localizada
            return i;

        }

    }

    return -1;

}

// Essa funcao serve para formar a lista de adjacencia, sempre que um elemento tem relacao outro, ele eh adicionado na lista
void inserirRelacoesMatriz(int matriz[TAM][TAM], TLista *vetor, char *nomeCidade1, char *nomeCidade2, int distancia)
{
    // Os parametros passados nas funcoes sao: a posicao no vetor que o elemento sera inserido, o nome da cidade que sera inserida e a distancia entre as cidades
    int posicaoCidade1, posicaoCidade2;

    posicaoCidade1 = encontrarPosicaoCidade(vetor, nomeCidade1);
    posicaoCidade2 = encontrarPosicaoCidade(vetor, nomeCidade2);
    matriz[posicaoCidade1][posicaoCidade2] = distancia;

    // Inseri o nome da cidade 2 na lista de adjacencia da cidade 1
    inserirNomeCidades(&vetor[posicaoCidade1], vetor[posicaoCidade2].inicio->nome, distancia);

}

/* ================================================================= */
void imprimirVertices(TLista *vetor)
{

    int i;
    printf("\n\n");
    
    // Percorre o vetor sempre printando o elemento da primeira posicao da lista
    for(i = 0; i < TAM; i++){
        printf("(%d) - %s", i, vetor[i].inicio->nome);
    }
    printf("\n");

}

// Funcao para exibir cada elemento da lista de uma determinada posicao do vetor
void exibir_lista(TLista *lista)
{
	TVertice *atual = lista->inicio;

	while(atual != NULL){
		printf("\t(%d) \t%s", atual->distancia, atual->nome);
		atual = atual->prox;
	}

    printf("\n");

}

// Percorre o vetor e chama uma funcao para mostrar a lista de cada posicao do vetor
void exibir_vetor(TLista *vetor)
{
	int i;

	for(i = 0; i < TAM; i++){
		printf("%d - " ,i);
		// E passado como parametro cada posição do vetor para ser listado no exibir_lista()
		exibir_lista(&vetor[i]);

	}
}

// Conferir se a cidade ja existe na lista de cidades de menor distancia
int cidadeDisponivel(TLista *listaCidadesInseridas, char *cidade)
{

    TVertice *atual = listaCidadesInseridas->inicio;

    while (atual != NULL)
    {

        if(strcmp(atual->nome, cidade) == 0){
            // Se a cidade for encontrado na lista retorna -1
            return -1;
        }

        atual = atual->prox;
    }

    return 1;

}

// Percorrer cada lista de cada posicao do vetor e retornar a menor Vertice (cidade com menor distancia)
TVertice *menorDistanciaLista(TLista *lista, TLista *listaCidadesInseridas)
{

    TVertice *atualVertice = lista->inicio;
    TVertice *menor = NULL;
    int validado;

    while (atualVertice != NULL)
    {
        // Conferir se a cidade ja foi inserida na lista de cidades com menor distancia
        validado = cidadeDisponivel(listaCidadesInseridas, atualVertice->nome);

        // Se a cidade nao estiver na lista sera conferido se ela tem a menor distancia
        if (validado == 1){

            if (menor == NULL){
                menor = atualVertice;

            } else {

                if (atualVertice->distancia < menor->distancia){
                    menor = atualVertice;
                    
                }

            }

        }

        atualVertice = atualVertice->prox;
        
    }

    // Retorna a menor cidade da lista
    return menor;
}

TVertice *menorDistanciaParcial(TLista *vetorCidades, int qtdeCidadesInseridas, int *vetorPosicaoCidades, TLista *listaCidadesInseridas)
{

    // Menor parcial para armazenar a menor distancia momentanea de cada cidade no for
    TVertice *menorParcial = NULL;

    // Armazenar a menor distancia entre as posicoes do FOR
    TVertice *menorTodos;
    menorTodos = NULL;

    // 'qtdeCidadeInseridas' armazena o tamanho momentaneo do vetor que possui a posicao das cidades
    int i;
    for(i = 0; i <= qtdeCidadesInseridas - 1; i++){

        menorParcial = menorDistanciaLista(&vetorCidades[vetorPosicaoCidades[i]], listaCidadesInseridas);

        if(menorParcial != NULL)
        {
            // Descobir a menor distancia das cidades
            if(menorTodos == NULL){

                menorTodos = menorParcial;

            } else if (menorParcial->distancia < menorTodos->distancia){

                menorTodos = menorParcial;

            }

        }

    }

    return menorTodos;

}

void distancia(TLista *vetorCidades, TLista *listaCidadesInseridas, char *nomeCidade)
{

    // Toda vez que entrar nessa funcao a lista de cidades com menor caminho sera inicializada
    inicializaLista(listaCidadesInseridas);

    // Armazenar o total percorrido
    int totalPercorrido = 0;

    // Vetor que armazenara a posicao que cada cidade ocupa no vetor do tipo TLista
    int vetorPosicaoCidades[TAM+1];
    // Variavel utilizada para armazenar a quantidade de cidades inseridas na lista de menor distancia
    int qtdeCidadesInseridas = 0;
    int posicao=0;

    // Armazenara a menor vertice (nome, distancia)
    TVertice *menorTodos = (TVertice *)malloc(sizeof(TVertice));

    // Encontrar a posicao da primeira cidade
    posicao = encontrarPosicaoCidade(vetorCidades, nomeCidade);

    // Inserir a posicao encontrada na posicao 0 do vetor que armazena a posicao das cidades
    vetorPosicaoCidades[0] = posicao;

    // Esse for garante que todas as cidades estejam na lista de menor distancia
    int i;
    for(i = 0; i < TAM; i++){

        qtdeCidadesInseridas++;

        // Vertice com menor distancia
        menorTodos = menorDistanciaParcial(vetorCidades, qtdeCidadesInseridas, vetorPosicaoCidades, listaCidadesInseridas);

        // Encontrar a posicao da cidade 'menorTodos'
        posicao = encontrarPosicaoCidade(vetorCidades, menorTodos->nome);

        // Adciona a posicao no vetor
        vetorPosicaoCidades[qtdeCidadesInseridas] = posicao;

        // Aumenta o total percorrido
        totalPercorrido += menorTodos->distancia;
        // Inseri o 'menorTodos' na lista de cidades de menor distancia
        inserirNomeCidades(listaCidadesInseridas, menorTodos->nome, menorTodos->distancia);
    }

    // No final da lista insere o total percorrido e a distancia total percorrida
    inserirNomeCidades(listaCidadesInseridas, "Total Percorrido: ", totalPercorrido);

}

// Funcao utiliza para mostrar a lista de cidades de menor distancia e o total percorrido naquela lista
void imprimirCidadesDistancia(TLista *listaCidades)
{

    TVertice *atualVertice = listaCidades->inicio;

    while (atualVertice != NULL)
    {
        if(atualVertice->prox != NULL){
            printf("Cidade: %s", atualVertice->nome);
            printf("Distancia para a cidade: %d\n\n", atualVertice->distancia);

        } else {
            // Nesse 'else' sera mostrado o total percorrido
            printf("%s: %d\n", atualVertice->nome, atualVertice->distancia);

        }

        atualVertice = atualVertice->prox;
    }
    

}
