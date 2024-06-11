#include <stdio.h>
#include <limits.h> // Para usar INT_MAX
#include <stdbool.h> // Para usar bool, true, false

#define V 5 // Número de vértices no grafo

// Função que implementa o algoritmo de Dijkstra para um grafo representado usando uma matriz de adjacência
void dijkstra(int graph[V][V], int src) {
    int dist[V]; // Array para armazenar a menor distância do vértice fonte até cada vértice
    bool sptSet[V]; // sptSet[i] será verdadeiro se o vértice i estiver incluído na árvore de menor caminho

    // Inicializa todas as distâncias como INFINITO e sptSet[] como falso
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    // A distância do vértice fonte para ele mesmo é sempre 0
    dist[src] = 0;

    // Encontra o menor caminho para todos os vértices
    for (int count = 0; count < V - 1; count++) {
        // Encontra o vértice com a menor distância que ainda não foi processado
        int min = INT_MAX, u;
        for (int v = 0; v < V; v++)
            if (!sptSet[v] && dist[v] <= min) {
                min = dist[v];
                u = v;
            }

        // Marca o vértice como processado
        sptSet[u] = true;

        // Atualiza o valor dist[] dos vértices adjacentes do vértice escolhido
        for (int v = 0; v < V; v++)
            // Atualiza dist[v] se não estiver em sptSet, existir uma aresta de u para v, e o caminho total de src para v através de u for menor que o valor atual de dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    // Imprime o array de distâncias construído
    printf("Vértice \t Distância da Fonte\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

// Função principal
int main() {
    // Exemplo de grafo representado por uma matriz de adjacência
    int graph[V][V] = {
        {0, 10, 0, 0, 5},
        {10, 0, 1, 0, 2},
        {0, 1, 0, 4, 0},
        {0, 0, 4, 0, 3},
        {5, 2, 0, 3, 0}
    };

    // Chamando a função dijkstra com o vértice fonte como 0
    dijkstra(graph, 0);

    return 0;
}
