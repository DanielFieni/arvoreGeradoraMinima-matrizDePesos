#include "lista.h"

int main(int argc, char *argv[])
{

    FILE *arq;
    char nomeCidade[30];
    char nomeCidade2[30];
    int distanciaCidades;

    int opcao;

    // Matriz apenas ilustrativa
    int matriz[TAM][TAM];

    // Vetor do tipo Lista para guarda a posicao de cada cidade
    TLista vetor[TAM];

    // Lista que sera usada armazenar o menor caminho percorrido e o total percorrido
    TLista *listaCidades;
    
    inicializarMatriz(matriz);
    inicializaVetor(vetor);
    inicializaLista(listaCidades);

    //  Arquivo contendo as cidades que serao inseridas
    arq = fopen("nomeCidadesFile.txt", "r");

    int i = 0;
    while(fgets(nomeCidade, 256, arq)){

        // Inserir as cidades nas suas posicoes, toda cidade no inicio tera distancia 0
        inserirNomeCidades(&vetor[i], nomeCidade, 0);
        i++;

    }

    fclose(arq);

    // Arquivo contento as relacoes entre as cidades
    arq = fopen("relacoesCidades.txt", "r");

    while(fgets(nomeCidade, 256, arq))
    {
        fgets(nomeCidade2, 256, arq);
        fscanf(arq, "%d\n", &distanciaCidades);
        
        inserirRelacoesMatriz(matriz, vetor, nomeCidade, nomeCidade2, distanciaCidades);

    }

    fclose(arq);

    do{
        opcao = menu();
        switch (opcao)
        {
            case 1: 
                // Imprimir Matriz
                imprimirMatriz(matriz);
                break;

            case 2: 
                // Imprimir relacoes das cidades
                exibir_vetor(vetor);
                break;

            case 3: 
                // Imprimir cidades Inseridas
                imprimirVertices(vetor);
                break;

            case 4:
                printf("\n");

                printf("Insira o nome da CIDADE para comecar: ");
                scanf(" %99[^\n]s", nomeCidade);
                // Concatenei o '\n' com com o nome da cidade. Fiz isso porque as cidades retiradas do arquivo vem com '\n'
                // Ja que o 'strcat' nao estava funcionando na minha máquina, optei por utilizar o 'strncat' para concatenar
                strncat(nomeCidade, "\na", 1);
                
                // Conferir se a cidade existe na lista de cidades inserias
                if(encontrarPosicaoCidade(vetor, nomeCidade) != -1){

                    // Se existir sera mostrado o menor caminho a partir daquela cidade
                    distancia(vetor, listaCidades, nomeCidade);
                    imprimirCidadesDistancia(listaCidades);
                } else {

                    printf("\nCidade NAO ENCONTRADA\n");
                }
                
                printf("\n");
                break;
        
        }

        system("pause");

    }while (opcao != 0);

    return 0;
}
