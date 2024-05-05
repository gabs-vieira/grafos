#include <stdio.h>

#define V 8

// Função DFS recursiva
void dfs(int graph[V][V], int startVertex, int visited[]) {
    // Marca o vértice atual como visitado e o imprime
    visited[startVertex] = 1;
    printf("Visitando vértice: %d\n", startVertex);

    // Percorre todos os vértices adjacentes ao vértice atual
    for (int i = 0; i < V; i++) {
        // Se o vértice adjacente não foi visitado e há uma aresta para ele, chama DFS recursivamente
        if (!visited[i] && graph[startVertex][i]) {
            dfs(graph, i, visited);
        }
    }
}

int main() {
    int graph[V][V] = {
        {0, 1, 1, 0, 0, 0, 0, 0},
        {1, 0, 0, 1, 1, 0, 0, 0},
        {1, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 1, 0, 0},
        {0, 1, 1, 0, 0, 1, 1, 0},
        {0, 0, 0, 1, 1, 0, 0, 1},
        {0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0}
    };

    // Array para marcar os vértices visitados
    int visited[V] = {0};

    // Chama a função DFS a partir do vértice 0
    printf("DFS traversal:\n");
    dfs(graph, 0, visited);

    return 0;
}
