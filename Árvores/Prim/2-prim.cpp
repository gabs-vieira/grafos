#include <stdio.h>
#include <stdbool.h>

#define V 5 // Número de vértices no grafo

// Função para encontrar o vértice com a menor chave que ainda não está incluído na MST
int minKey(int key[], bool mstSet[]) {
    int min = 1000; // Valor grande para inicialização
    int min_index = 0;

    // Percorre todos os vértices
    for (int v = 0; v < V; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }

    return min_index;
}

// Função para imprimir a MST
void printMST(int parent[], int graph[V][V]) {
    printf("Aresta   Peso\n");
    for (int i = 1; i < V; i++) {
        printf("%d - %d    %d \n", parent[i], i, graph[i][parent[i]]);
    }
}

// Função para construir a MST usando o algoritmo de Prim
void primMST(int graph[V][V]) {
    int parent[V]; // Para armazenar a MST
    int key[V];    // Chaves usadas para escolher a menor aresta
    bool mstSet[V]; // Para representar os vértices incluídos na MST

    // Inicializa todos os valores como "infinito" (ou um valor muito grande)
    for (int i = 0; i < V; i++) {
        key[i] = 1000;
        mstSet[i] = false;
    }

    // O primeiro vértice é sempre a raiz
    key[0] = 0;
    parent[0] = -1;

    // Constrói a MST
    for (int count = 0; count < V - 1; count++) {
        // Escolhe o vértice de menor chave
        int u = minKey(key, mstSet);
        mstSet[u] = true;

        // Atualiza os valores das chaves dos vértices adjacentes
        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Imprime a MST
    printMST(parent, graph);
}

int main() {
    // Grafo representado como uma matriz de adjacência
    int graph[V][V] = {
        { 0, 2, 0, 6, 0 },
        { 2, 0, 3, 8, 5 },
        { 0, 3, 0, 0, 7 },
        { 6, 8, 0, 0, 9 },
        { 0, 5, 7, 9, 0 }
    };

    // Chama a função para encontrar e imprimir a MST
    primMST(graph);

    return 0;
}
