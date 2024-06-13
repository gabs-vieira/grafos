#include<stdio.h>
#include<stdlib.h>

//Grafo geral
int grafo[1000][1000]; // colocando ele como 



// PRINTS
void imprimirLowpoints(int *lowpoints, int nVertices){
    for (int i = 0; i < nVertices; i++)
        printf("%d: %d\n", i+1, lowpoints[i]);
}

void imprimirPontes(int *lowpoints, int nVertices){
    printf("Pontes: ");

    int temPontes = 0;

    for(int i = 1; i<nVertices; i++){
        for(int j = 1; j<nVertices; j++){
            if(grafo[i][j] == 2 && lowpoints[j] == j)
                printf("%d %d\n", i, j);
                temPontes = 1;
        }
    }
    if (temPontes != 0){
        printf("Nenhuma\n");
    }
    printf("\n");
    
}



void dfs(int vertice, int nivel_corrente, int *niveis, int nVertices)
{
    niveis[vertice] = nivel_corrente;
    for (int i = 0; i < nVertices; i++)
    {
        if (grafo[vertice][i] == 1 && niveis[i] == -1)
        {
            grafo[vertice][i] = 2;
            grafo[i][vertice] = 0;
            dfs(i, nivel_corrente + 1, niveis, nVertices);
        }
    }
}

int lowpoint(int vertice, int *lowpoints, int *niveis, int nVertices)
{
    for (int origem = 0; origem < nVertices; origem++)
        for (int destino = 0; destino < nVertices; destino++)
            if (grafo[origem][destino] == 1 && niveis[origem] < niveis[destino])
                grafo[origem][destino] = 0;

    if (lowpoints[vertice] != -1)
        return lowpoints[vertice];

    lowpoints[vertice] = vertice;

    for (int i = 0; i < nVertices; i++)
    {
        if (grafo[vertice][i] == 2 && niveis[lowpoint(i, lowpoints, niveis, nVertices)] < niveis[lowpoints[vertice]])
            lowpoints[vertice] = lowpoints[i];
        else if (grafo[vertice][i] == 1 && niveis[i] < niveis[lowpoints[vertice]])
            lowpoints[vertice] = i;
    }

    return lowpoints[vertice];
}

int main(){

    //Ler arquivo
    FILE *file;
    file = fopen("arquivo.txt", "r");

    //Número de grafos
    int numeroGrafos;
    fscanf(file, "%d", &numeroGrafos);

    for (int i = 0; i < numeroGrafos; i++){

        //Ler número de vértices e arestas
        int numeroVertices, numeroArestas;
        fscanf(file, "%d %d", &numeroVertices, &numeroArestas);

        //Lógica para o GRAFO
        //Inicializar o grafo/Resetar o grafo
        for (int j = 0; j < 1000; j++){
            for (int k = 0; k < 1000; k++){
                grafo[j][k] = 0;
            }
        }

        //Ler arestas
        for (int j = 0; j < numeroArestas; j++){
            int origem, destino;
            fscanf(file, "%d %d", &origem, &destino);
            grafo[origem-1][destino-1] = 1;
            grafo[destino-1][origem-1] = 1;
        }

        int niveis[numeroVertices];
        int lowpoits[numeroVertices]; 
        for(int i=0; i<numeroVertices; i++) niveis[i] = lowpoits[i] = -1;


        //Transformar o grafo não dirigido em dirigido
        dfs(1, 0, niveis, numeroVertices);
        //Calcular os lowpoints
        lowpoint(1, lowpoits, niveis, numeroVertices);

        int marcadores[numeroVertices];
        int articulacoes[numeroVertices];
        //Inicializar marcadores e articulações
        for (int i = 0; i < numeroVertices; i++){
            marcadores[i] = 0;
            articulacoes[i] = 0;
        }







        //Verificar se é articulação pra Raiz
        int raiz = 1, filhos = 0;
        for (int destino = 1; destino < numeroVertices; destino++)
            if (grafo[raiz][destino] == 2)
            {
                filhos++;
                marcadores[raiz] = destino;
                if (filhos > 2)
                    articulacoes[raiz] = raiz;
            }

        //Verificar se é articulação para os outros vértices
        for (int origem = 1; origem < numeroVertices; origem++)
            for (int destino = 1; destino < numeroVertices; destino++)
                if (grafo[origem][destino] == 2 && (lowpoits[destino] == origem || lowpoits[destino] == destino))
                {
                    marcadores[origem] = destino;
                    if (origem != raiz)
                        articulacoes[origem] = origem;
                }


        //Imprimir lowpoints
        imprimirLowpoints(lowpoits, numeroVertices);

        //Imprimir as Pontes
        imprimirPontes(lowpoits, numeroVertices);

        //Imprimir as Articulações
        printf("Articulacoes: ");
        for (int i = 1; i < numeroVertices; i++)
            if (articulacoes[i] != 0)
                printf("%d ", i);

        //Imprimir Demarcadores
        printf("\nDemarcadores: ");
        for (int i = 1; i < numeroVertices; i++)
            if (marcadores[i] != 0)
                printf("%d ", i);

        printf("\n\n");

    }

    return 0;
}