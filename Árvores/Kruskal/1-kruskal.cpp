#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar uma aresta de um grafo
struct Edge {
    int src, dest, weight;
};

// Estrutura para representar um grafo
struct Graph {
    int V, E; // V é o número de vértices e E é o número de arestas
    struct Edge* edge; // Array de arestas
};

// Estrutura para representar um subconjunto para o algoritmo Union-Find
struct Subset {
    int parent;
    int rank;
};

// Função para criar um grafo com V vértices e E arestas
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge*) malloc(graph->E * sizeof(struct Edge));
    return graph;
}

// Função para encontrar o conjunto de um elemento i (usando o caminho de compressão)
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Função para unir dois subconjuntos x e y (usando união por rank)
void Union(struct Subset subsets[], int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank)
        subsets[rootX].parent = rootY;
    else if (subsets[rootX].rank > subsets[rootY].rank)
        subsets[rootY].parent = rootX;
    else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

// Função de comparação para ordenar as arestas de acordo com seus pesos
int compareEdges(const void* a, const void* b) {
    struct Edge* a1 = (struct Edge*) a;
    struct Edge* b1 = (struct Edge*) b;
    return a1->weight > b1->weight;
}

// Função principal para executar o algoritmo de Kruskal
void KruskalMST(struct Graph* graph) {
    int V = graph->V;
    struct Edge result[V]; // Array para armazenar o resultado
    int e = 0; // Índice usado para result[]
    int i = 0; // Índice usado para arestas ordenadas

    // Passo 1: Ordenar todas as arestas em ordem não decrescente de peso
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), compareEdges);

    // Alocar memória para criar V subconjuntos
    struct Subset* subsets = (struct Subset*) malloc(V * sizeof(struct Subset));

    // Criar V subconjuntos com elementos únicos
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Número de arestas para ser incluídas na MST é V-1
    while (e < V - 1 && i < graph->E) {
        // Passo 2: Selecionar a menor aresta. Verificar se forma um ciclo com a MST formada até agora
        struct Edge next_edge = graph->edge[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        // Se incluir esta aresta não forma um ciclo, incluir no resultado e incrementar o índice do resultado
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    // Imprimir a MST construída
    printf("As arestas na MST são:\n");
    for (i = 0; i < e; ++i)
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);

    // Liberar a memória alocada
    free(subsets);
}

int main() {
    /* Exemplo de grafo:
        4 -- 1 == 2
        4 -- 2 == 3
        1 -- 2 == 1
        1 -- 3 == 4
        2 -- 3 == 5
    */

    int V = 4; // Número de vértices no grafo
    int E = 5; // Número de arestas no grafo
    struct Graph* graph = createGraph(V, E);

    // Aresta 0-1 (custo 10)
    graph->edge[0].src = 0;
    graph->edge[0].dest = 1;
    graph->edge[0].weight = 10;

    // Aresta 0-2 (custo 6)
    graph->edge[1].src = 0;
    graph->edge[1].dest = 2;
    graph->edge[1].weight = 6;

    // Aresta 0-3 (custo 5)
    graph->edge[2].src = 0;
    graph->edge[2].dest = 3;
    graph->edge[2].weight = 5;

    // Aresta 1-3 (custo 15)
    graph->edge[3].src = 1;
    graph->edge[3].dest = 3;
    graph->edge[3].weight = 15;

    // Aresta 2-3 (custo 4)
    graph->edge[4].src = 2;
    graph->edge[4].dest = 3;
    graph->edge[4].weight = 4;

    // Executar algoritmo de Kruskal para encontrar MST
    KruskalMST(graph);

    // Liberar a memória alocada
    free(graph->edge);
    free(graph);

    return 0;
}
