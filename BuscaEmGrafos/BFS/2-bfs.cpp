#include <stdio.h>
#include <stdbool.h>

#define V 8 // Número de vértices

// Função para realizar a busca em largura
void bfs(int graph[V][V], int startVertex) {
    // Vetor para marcar os vértices visitados
    bool visited[V] = {false};
    
    // Inicializa uma fila para armazenar os vértices a serem visitados
    int queue[V], front = 0, rear = -1;
    /*
        Front = marca o inicio da fila e também como os vértices estão sendo visitados/percorridos
        Rear  = Marca a última posição que foi adicionado na fila 
    **/

    // Adiciona o vértice inicial à fila e marca como visitado
    queue[++rear] = startVertex;
    visited[startVertex] = true;

    // Enquanto a fila não estiver vazia
    while (front <= rear) {
        // Remove o primeiro vértice da fila
        int currentVertex = queue[front++];

        printf("Visitando vértice: %d\n", currentVertex);

        // Percorre todos os vértices adjacentes ao vértice atual
        for (int i = 0; i < V; i++) {
            if (graph[currentVertex][i] && !visited[i]) {
                queue[++rear] = i;
                visited[i] = true;
            }
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


    // Define o vértice inicial para a busca
    int startVertex = 1;

    // Chama a função BFS a partir do vértice inicial
    printf("BFS começando do vértice %d:\n", startVertex);
    bfs(graph, startVertex);

    return 0;
}
