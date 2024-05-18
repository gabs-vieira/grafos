#include <stdio.h>
#include <stdbool.h>

#define V 5 // Número de vértices

void primMST(int graph[V][V], int vertice_inicial)
{
    int parent[V];    // Armazena a MST. Cada índice representa um vértice, e o valor armazenado no índice representa o pai desse vértice na MST.
    int distancia[V]; // Armazena as chaves usadas para escolher a menor aresta que conecta o vértice à MST.
    bool mst[V];      // Para representar os vértices incluídos na MST

    // Inicializar todas as distâncias como infinito e os vértices da MST como false
    for (int i = 0; i < V; i++)
    {
        distancia[i] = 1000; // Define todas as distâncias como um valor grande
        mst[i] = false;      // Nenhum vértice está incluído na MST inicialmente
    }

    // Está sendo passado um vértice inicial, então este tem que atualizar a distância dele mesmo, e também este mesmo vértice não tem pai.
    // O primeiro vértice é sempre a raiz.
    distancia[vertice_inicial] = 0; // Distância do vértice inicial para ele mesmo é 0
    parent[vertice_inicial] = -1;   // O vértice inicial não tem pai

    // Construindo MST
    for (int i = 0; i < V - 1; i++)
    { // V-1 iterações para construir a MST

        int min = 1000; // Inicializa a menor distância como um valor grande
        int u = 0;      // Índice do vértice de menor valor

        // Percorre todos os vértices e pega o vértice de menor valor
        for (int j = 0; j < V; j++)
        {
            if (!mst[j] && distancia[j] < min)
            {
                min = distancia[j];
                u = j;
            }
        }

        mst[u] = true; // Inclui o vértice de menor valor na MST

        // Atualiza os valores das distâncias dos vértices adjacentes ao menor vértice encontrado anteriormente
        for (int v = 0; v < V; v++)
        {
            // Se o vértice v não estiver na MST e a aresta (u, v) existe e é menor que a distância atual
            if (graph[u][v] && !mst[v] && graph[u][v] < distancia[v])
            {
                parent[v] = u;              // O pai do vértice v é u
                distancia[v] = graph[u][v]; // Atualiza a distância do vértice v
            }
        }
    }

    // Imprime a MST
    int soma = 0;
    printf("Aresta   Peso\n");
    for (int i = 1; i < V; i++)
    {
        printf("%d - %d     %d\n", parent[i], i, graph[i][parent[i]]);
        soma += graph[i][parent[i]];
    }

    printf("\nValor total da MST: %d\n", soma);
}

int main()
{
    // Grafo representado como uma matriz de adjacência
    int graph[V][V] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}};

    int vi;
    printf("Digite o vértice inicial: ");
    scanf("%d", &vi);

    // Chama a função para encontrar e imprimir a MST
    primMST(graph, vi);

    return 0;
}

/**
 * Uma MST de um grafo com V vértices possui exatamente V−1 arestas. Isso ocorre porque, em uma árvore, sempre há um vértice a menos do que o número de arestas (uma árvore com n vértices tem n−1 arestas).
 */
