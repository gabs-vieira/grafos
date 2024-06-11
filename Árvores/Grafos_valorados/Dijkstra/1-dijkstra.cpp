// Algoritmos de grafos valorados consideram todos os caminhos entre dois vértices
// Eles respondem o problema do caminho.


#include <stdio.h>
#include <limits.h> // Para usar INT_MAX
#include <stdbool.h> // Para usar bool, true, false

#define V 5 // Número de vértices no grafo

// Função para encontrar o vértice com a menor distância que ainda não foi incluído na árvore de menor caminho
int minDistance(int dist[], bool sptSet[]) {
    // Inicializa o valor mínimo
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }

    return min_index;
}

// Função para imprimir o array de distâncias
void printSolution(int dist[]) {
    printf("Vértice \t Distância da Fonte\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

// Função que implementa o algoritmo de Dijkstra para um grafo representado usando uma matriz de adjacência
void dijkstra(int graph[V][V], int src) {
    int dist[V]; // Array para segurar a menor distância do caminho árvore

    bool sptSet[V]; // sptSet[i] será true se o vértice i está incluído no menor caminho da árvore ou a menor distância até i está finalizada

    // Inicializa todas as distâncias como INFINITO e sptSet[] como false
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    // Distância do vértice origem para ele mesmo é sempre 0
    dist[src] = 0;

    // Encontra o menor caminho para todos os vértices
    for (int count = 0; count < V - 1; count++) {
        // Escolhe o vértice de menor distância do conjunto de vértices ainda não processados.
        int u = minDistance(dist, sptSet);

        // Marca o vértice como processado
        sptSet[u] = true;

        // Atualiza o valor dist[] dos vértices adjacentes do vértice escolhido.
        for (int v = 0; v < V; v++)
            // Atualiza dist[v] se não estiver em sptSet, existe uma aresta de u para v, e o caminho total de src para v através de u é menor que o valor atual de dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    // Imprime o array de distâncias construído
    printSolution(dist);
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
