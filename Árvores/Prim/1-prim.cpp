#include <stdio.h>
#include <stdbool.h>

#define V 5 // Número de vértices no grafo

// Função para encontrar o vértice com a chave de valor mínimo
int minKey(int key[], bool mstSet[]) {
    int min = 1000, min_index;

    // Itera por todos os vértices para encontrar o mínimo não incluído na MST
    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

// Função para construir e imprimir a MST para um grafo representado usando uma matriz de adjacência
void primMST(int graph[V][V]) {
    int parent[V]; // Para armazenar a MST construída
    int key[V];    // Chaves usadas para escolher o mínimo peso da aresta no corte
    bool mstSet[V]; // Para representar os vértices incluídos na MST

    // Inicializa todas as chaves como um valor grande e mstSet[] como falso
    for (int i = 0; i < V; i++)
        key[i] = 1000, mstSet[i] = false;

    // A raiz sempre será o primeiro vértice
    key[0] = 0;
    parent[0] = -1; // O primeiro nó não tem pai

    // Constrói a MST
    for (int count = 0; count < V - 1; count++) {
        // Escolhe o vértice de menor chave do conjunto de vértices ainda não incluídos na MST
        int u = minKey(key, mstSet);
        mstSet[u] = true;

        // Atualiza as chaves e os pais dos vértices adjacentes do vértice escolhido
        for (int v = 0; v < V; v++)
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }

    // Imprime a MST
    printf("Aresta   Peso\n");
    for (int i = 1; i < V; i++)
        printf("%d - %d    %d \n", parent[i], i, graph[i][parent[i]]);
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
