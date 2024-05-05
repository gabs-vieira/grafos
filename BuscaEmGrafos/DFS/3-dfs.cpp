#include <stdio.h>
#include <stdbool.h>

#define V 8 // Número de vértices

// Função para realizar a busca em profundidade a partir de um vértice específico
void dfs(int graph[V][V], int startVertex, bool visited[V]) {
    // Marca o vértice atual como visitado
    visited[startVertex] = true;
    printf("Visitando vértice: %d\n", startVertex);

    // Percorre todos os vértices adjacentes ao vértice atual
    for (int i = 0; i < V; i++) {
        // Verifica se o vértice i é adjacente ao vértice atual e se não foi visitado
        if (graph[startVertex][i] && !visited[i]) {
            // Chama a função recursivamente para visitar o vértice i
            dfs(graph, i, visited);
        }
    }
}

// Função para chamar a DFS a partir de todos os vértices não visitados
void dfsTraversal(int graph[V][V]) {
    // Vetor para marcar os vértices visitados
    bool visited[V] = {false};

    // Percorre todos os vértices, chamando a DFS a partir de vértices não visitados
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
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

    // Chama a função DFS a partir de todos os vértices
    printf("DFS traversal:\n");
    dfsTraversal(graph);

    return 0;
}
