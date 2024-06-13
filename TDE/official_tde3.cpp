#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 1000

int grafo[MAX_VERTICES][MAX_VERTICES];

// DFS para transformar o grafo não dirigido em dirigido
void dfs(int vertice, int nivel_corrente, int *niveis, int nVertices) {
    niveis[vertice] = nivel_corrente;
    for (int i = 0; i < nVertices; i++) {
        if (grafo[vertice][i] == 1 && niveis[i] == -1) {
            grafo[vertice][i] = 2;  // Marcar aresta de árvore
            grafo[i][vertice] = 0;  // Remover aresta não direcionada
            dfs(i, nivel_corrente + 1, niveis, nVertices);
        }
    }
}

// Função para calcular lowpoints
int lowpt(int vertice, int *low, int *niveis, int nVertices) {
    if (low[vertice] != -1) return low[vertice];

    low[vertice] = vertice;

    for (int i = 0; i < nVertices; i++) {
        if (grafo[vertice][i] == 2) { // Aresta de árvore
            int low_i = lowpt(i, low, niveis, nVertices);
            if (niveis[low_i] < niveis[low[vertice]]) {
                low[vertice] = low_i;
            }
        } else if (grafo[vertice][i] == 1) { // Aresta de retorno
            if (niveis[i] < niveis[low[vertice]]) {
                low[vertice] = i;
            }
        }
    }

    return low[vertice];
}

// Função para identificar e imprimir as pontes do grafo
void pontes(int *lowpoints, int numeroVertices) {
    printf("Pontes: ");
    int temPontes = 0;
    for (int i = 0; i < numeroVertices; i++) {
        for (int j = 0; j < numeroVertices; j++) {
            if (grafo[i][j] == 2 && lowpoints[j] == j) {
                printf("(%d, %d)\n", i + 1, j + 1);
                temPontes = 1;
            }
        }
    }
    if (!temPontes) {
        printf("Nenhuma\n");
    }
}

// Função para imprimir o grafo
void printar_grafo(int numeroVertices) {
    for (int i = 0; i < numeroVertices; i++) {
        for (int j = 0; j < numeroVertices; j++) {
            printf("%d ", grafo[i][j]);
        }
        printf("\n");
    }
}

// Função para imprimir os lowpoints
void printar_lowpoints(int *lowpoints, int numeroVertices) {
    printf("Lowpoints: ");
    for (int i = 0; i < numeroVertices; i++) {
        printf("%d:%d ", i + 1, lowpoints[i] + 1);
    }
    printf("\n");
}

// Função para imprimir os biconexos
void print_componentesBiconexos(int *marcadores, int *articulacoes, int raiz, int numeroVertices) {
    printf("Componentes Biconexos: ");

    bool temBicomponents = false;

    // Verificar articulações
    for (int i = numeroVertices - 1; i > 0; i--) {
        if (articulacoes[i] != 0) {
            printf(" {%d", i + 1);
            for (int j = 0; j < numeroVertices; j++) {
                if (grafo[i][j] == 2) {
                    printf(",%d", j + 1);
                    grafo[i][j] = 0;
                }
            }
            printf("} ");
            temBicomponents = true;
        }
    }

    // Verificar marcadores
    if (!temBicomponents) {
        printf(" {%d", raiz + 1);
        for (int i = 0; i < numeroVertices; i++) {
            for (int j = 0; j < numeroVertices; j++) {
                if (grafo[i][j] == 2) {
                    printf(",%d", j + 1);
                }
            }
        }
        printf("} ");
    }

    printf("\n");
}

int main() {
    // Ler arquivo
    FILE *file;
    file = fopen("arquivo.txt", "r");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Número de grafos
    int numeroGrafos;
    fscanf(file, "%d", &numeroGrafos);

    for (int g = 0; g < numeroGrafos; g++) {
        // Ler número de vértices e arestas
        int numeroVertices, numeroArestas;
        fscanf(file, "%d %d", &numeroVertices, &numeroArestas);

        // Inicializar/resetar o grafo
        for (int i = 0; i < numeroVertices; i++) {
            for (int j = 0; j < numeroVertices; j++) {
                grafo[i][j] = 0;
            }
        }

        // Ler o grafo
        for (int i = 0; i < numeroArestas; i++) {
            int origem, destino;
            fscanf(file, "%d %d", &origem, &destino);
            grafo[origem - 1][destino - 1] = 1;
            grafo[destino - 1][origem - 1] = 1;
        }

        // Criar vetor de níveis e lowpoints; Inicializar com -1
        int niveis[numeroVertices];
        int lowpoints[numeroVertices];
        for (int i = 0; i < numeroVertices; i++) {
            niveis[i] = lowpoints[i] = -1;
        }

        dfs(0, 0, niveis, numeroVertices); // Iniciar DFS a partir do vértice 0

        for (int i = 0; i < numeroVertices; i++) {
            lowpt(i, lowpoints, niveis, numeroVertices);
        }

        printar_lowpoints(lowpoints, numeroVertices);
        
        // Pontes do grafo
        pontes(lowpoints, numeroVertices);

        // Articulações e Marcadores
        int marcadores[MAX_VERTICES] = {0};
        int articulacoes[MAX_VERTICES] = {0};

        // Verificar se é articulação para a raiz
        int raiz = 0, filhos = 0;
        for (int destino = 0; destino < numeroVertices; destino++) {
            if (grafo[raiz][destino] == 2) {
                filhos++;
                marcadores[raiz] = destino;
                if (filhos > 1) {
                    articulacoes[raiz] = 1;
                }
            }
        }

        // Verificar se é articulação para os outros vértices
        for (int origem = 0; origem < numeroVertices; origem++) {
            if (origem == raiz) continue;

            for (int destino = 0; destino < numeroVertices; destino++) {
                if (grafo[origem][destino] == 2 && (lowpoints[destino] >= niveis[origem])) {
                    marcadores[origem] = destino;
                    if (origem != raiz) {
                        articulacoes[origem] = 1;
                    }
                }
            }
        }

        // Imprimir as Articulações
        printf("Articulações: ");
        for (int i = 0; i < numeroVertices; i++) {
            if (articulacoes[i] != 0) {
                printf("%d ", i + 1);
            }
        }

        // Imprimir Demarcadores
        printf("\nDemarcadores: ");
        for (int i = 0; i < numeroVertices; i++) {
            if (marcadores[i] != 0) {
                printf("%d ", marcadores[i] + 1);
            }
        }

        printf("\n");

        // Imprimir os biconexos
        print_componentesBiconexos(marcadores, articulacoes, raiz, numeroVertices);

        printf("\n");
    }

    fclose(file);
    return 0;
}
