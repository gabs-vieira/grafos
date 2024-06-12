#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 1000

// Estrutura para representar uma aresta
typedef struct {
    int u, v;
} Aresta;

// Estrutura para representar uma componente biconexa
typedef struct {
    int vertices[MAX_VERTICES];
    int tamanho;
} ComponenteBiconexa;

int numVertices, numArestas;
int grafo[MAX_VERTICES][MAX_VERTICES];
int visitado[MAX_VERTICES], desc[MAX_VERTICES], low[MAX_VERTICES], pai[MAX_VERTICES]; // Vetores auxiliares
bool articulacao[MAX_VERTICES];
Aresta arestas[MAX_VERTICES];
int contagemArestas = 0;
int tempo = 0;

ComponenteBiconexa componentesBiconexas[MAX_VERTICES];
int contagemComponentesBiconexas = 0;

int pilha[MAX_VERTICES][2];
int topo = -1;

// Inicializa o grafo e as estruturas auxiliares
void inicializaGrafo() {
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            grafo[i][j] = 0;
        }
        visitado[i] = 0;
        desc[i] = -1;
        low[i] = -1;
        pai[i] = -1;
        articulacao[i] = false;
    }
    contagemArestas = 0;
    tempo = 0;
    contagemComponentesBiconexas = 0;
    topo = -1;
}

// Adiciona uma aresta ao grafo
void adicionaAresta(int u, int v) {
    grafo[u][v] = 1;
    grafo[v][u] = 1;
}

// Empilha uma aresta (u, v) para rastrear componentes biconexas
void push(int u, int v) {
    topo++;
    pilha[topo][0] = u;
    pilha[topo][1] = v;
}

// Desempilha uma aresta
void pop() {
    topo--;
}

// Realiza a busca em profundidade (DFS) e calcula lowpoints, pontes e articulações
void DFS(int u) {
    visitado[u] = 1;
    desc[u] = low[u] = ++tempo;
    int filhos = 0;

    for (int v = 1; v <= numVertices; v++) {
        if (grafo[u][v]) {
            if (!visitado[v]) {
                filhos++;
                pai[v] = u;
                push(u, v);  // Empilha a aresta (u, v)
                DFS(v);

                low[u] = (low[u] < low[v]) ? low[u] : low[v];

                // Verifica se u é um ponto de articulação
                if ((pai[u] == -1 && filhos > 1) || (pai[u] != -1 && low[v] >= desc[u])) {
                    articulacao[u] = true;

                    // Cria uma nova componente biconexa
                    ComponenteBiconexa componente;
                    componente.tamanho = 0;
                    while (pilha[topo][0] != u || pilha[topo][1] != v) {
                        int a = pilha[topo][0];
                        int b = pilha[topo][1];
                        componente.vertices[componente.tamanho++] = a;
                        componente.vertices[componente.tamanho++] = b;
                        pop();
                    }
                    componente.vertices[componente.tamanho++] = u;
                    componente.vertices[componente.tamanho++] = v;
                    pop();
                    componentesBiconexas[contagemComponentesBiconexas++] = componente;
                }

                // Verifica se (u, v) é uma ponte
                if (low[v] > desc[u]) {
                    arestas[contagemArestas++] = (Aresta){u, v};
                }
            } else if (v != pai[u] && desc[v] < desc[u]) {
                low[u] = (low[u] < desc[v]) ? low[u] : desc[v];
                push(u, v);  // Empilha a aresta de retorno (u, v)
            }
        }
    }
}

// Imprime os lowpoints de cada vértice
void imprimeLowpoints() {
    printf("Lowpts: ");
    for (int i = 1; i <= numVertices; i++) {
        printf("%d:%d ", i, low[i]);
    }
    printf("\n");
}

// Imprime as pontes do grafo
void imprimePontes() {
    if (contagemArestas == 0) {
        printf("Pontes: nenhuma\n");
    } else {
        printf("Pontes: ");
        for (int i = 0; i < contagemArestas; i++) {
            printf("(%d,%d) ", arestas[i].u, arestas[i].v);
        }
        printf("\n");
    }
}

// Imprime os pontos de articulação do grafo
void imprimeArticulacoes() {
    bool temArticulacao = false;
    printf("Articulações: ");
    for (int i = 1; i <= numVertices; i++) {
        if (articulacao[i]) {
            printf("%d ", i);
            temArticulacao = true;
        }
    }
    if (!temArticulacao) {
        printf("nenhuma");
    }
    printf("\n");
}

// Imprime os demarcadores do grafo (pontos de articulação e filhos da raiz)
void imprimeDemarcadores() {
    printf("Demarcadores: ");
    for (int i = 1; i <= numVertices; i++) {
        if (articulacao[i] || pai[i] == 1) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

// Imprime os vértices que compõem cada componente biconexa
void imprimeComponentesBiconexas() {
    printf("Componentes biconexas: ");
    for (int i = 0; i < contagemComponentesBiconexas; i++) {
        printf("{");
        for (int j = 0; j < componentesBiconexas[i].tamanho; j++) {
            printf("%d", componentesBiconexas[i].vertices[j]);
            if (j < componentesBiconexas[i].tamanho - 1) {
                printf(",");
            }
        }
        printf("} ");
    }
    printf("\n");
}

// Lê o grafo a partir de um arquivo de entrada
void leGrafoDoArquivo(const char *filename) {
    FILE *arquivo = fopen(filename, "r");
    if (arquivo == NULL) {
        fprintf(stderr, "Não foi possível abrir o arquivo de entrada.\n");
        return;
    }

    int numGrafos;
    fscanf(arquivo, "%d", &numGrafos);

    for (int g = 0; g < numGrafos; g++) {
        fscanf(arquivo, "%d %d", &numVertices, &numArestas);
        inicializaGrafo();

        // Lê as arestas do grafo
        for (int i = 0; i < numArestas; i++) {
            int u, v;
            fscanf(arquivo, "%d %d", &u, &v);
            adicionaAresta(u, v);
        }

        // Executa DFS a partir do vértice 1
        DFS(1);

        // Imprime os resultados
        imprimeLowpoints();
        imprimePontes();
        imprimeArticulacoes();
        imprimeDemarcadores();
        imprimeComponentesBiconexas();
    }

    fclose(arquivo);
}

int main() {
    const char *filename = "arquivo.txt";
    leGrafoDoArquivo(filename);
    return 0;
}