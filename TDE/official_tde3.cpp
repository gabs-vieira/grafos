#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

int graph[MAX_N][MAX_N], level[MAX_N], low[MAX_N], num_children[MAX_N], parent[MAX_N], children[MAX_N][MAX_N];
int bridge = 0;

// Função para inicializar as variáveis
void initializeVariables(int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            graph[i][j] = 0;
        }
        level[i] = -1;
        low[i] = -1;
        parent[i] = -1;
        num_children[i] = 0;
    }
    bridge = 0;
}

// Função de busca em profundidade (DFS)
void dfs(int v, int current_parent, int N) {
    // Inicializa o tempo estático para a primeira chamada de DFS
    static int time = 0;

    // Define o nível e o valor low do vértice atual 'v' com base no tempo da visita
    level[v] = low[v] = ++time;

    // Define o pai do vértice atual
    parent[v] = current_parent;

    // Percorre todos os vértices para explorar os vizinhos do vértice 'v'
    for (int i = 0; i < N; i++) {
        // Se houver uma aresta entre 'v' e 'i'
        if (graph[v][i] == 1) {
            // Se o vértice 'i' não foi visitado (nível igual a -1)
            if (level[i] == -1) {
                // Adiciona 'i' como filho de 'v'
                children[v][num_children[v]++] = i;

                // Chama a DFS recursivamente para o vértice 'i'
                dfs(i, v, N);

                // Atualiza o valor low do vértice 'v' com o menor valor low de seus filhos
                low[v] = (low[i] < low[v]) ? low[i] : low[v];
            } 
            // Se 'i' já foi visitado e 'i' não é o pai do vértice 'v'
            else if (i != current_parent) {
                // Atualiza o valor low do vértice 'v' com o nível de 'i' se for menor
                low[v] = (level[i] < low[v]) ? level[i] : low[v];
            }
        }
    }
}

// Função para calcular os marcadores
int markers(int articulationArray[], int articulationSize, int *size, int N, int array[]) {
    int n = 0;
    int i, j;

    // Adiciona a quantidade de filhos das raízes (nós sem pai)
    for (int i = 0; i < N; i++) {
        if (parent[i] == -1) {
            n += num_children[i];
        }
    }

    // Adiciona a quantidade de filhos dos nós de articulação
    for (int i = 0; i < articulationSize; i++) {
        n += num_children[articulationArray[i]];
    }

    int index = 0;
    // Preenche o vetor com os filhos das raízes
    for (int i = 0; i < N; i++) {
        if (parent[i] == -1) {
            for (int j = 0; j < num_children[i]; j++) {
                array[index++] = children[i][j];
            }
        }
    }

    // Preenche o vetor com os filhos dos nós de articulação
    for (int i = 0; i < articulationSize; i++) {
        for (int j = 0; j < num_children[articulationArray[i]]; j++) {
            array[index++] = children[articulationArray[i]][j];
        }
    }

    // Atualiza o tamanho do vetor de marcadores
    *size = n;

    return n;
}

// Função para identificar nós de articulação
int articulations(int *size, int N, int array[]) {
    int n = 0;

    for (int i = 0; i < N; i++) {
        if (parent[i] == -1 && num_children[i] >= 2) {
            array[n++] = i;
        } else if (parent[i] != -1) {
            int isArticulation = 0;
            for (int j = 0; j < num_children[i]; j++) {
                if (low[children[i][j]] >= level[i]) {
                    isArticulation = 1;
                    break;
                }
            }
            if (isArticulation) {
                array[n++] = i;
            }
        }
    }

    *size = n;
    return n;
}

// Função para busca em largura (BFS)
void bfs(int vi, int N) {
    int queue[MAX_N], front = 0, rear = 0;
    queue[rear++] = vi;
    level[vi] = 0;

    while (front < rear) {
        int v = queue[front++];
        for (int i = 0; i < N; i++) {
            if (graph[v][i] && level[i] == -1) {
                queue[rear++] = i;
                level[i] = level[v] + 1;
            }
        }
    }
}

// Função para identificar componentes biconexas
void biconnectedComponents(int markers[], int markersSize, int articulationArray[], int articulationSize, int N) {
    int visited[MAX_N];
    int isArticulation = 0;

    for (int i = 0; i < N; i++) {
        visited[i] = 0;
        level[i] = -1;
    }

    printf("Biconnected Components: ");

    for (int i = markersSize - 1; i >= 0; i--) {
        for (int j = 0; j < N; j++) {
            level[j] = -1;
        }

        bfs(markers[i], N);

        isArticulation = 0;

        int first_printed = 0; // Controla a formatação das componentes biconexas

        printf("{");
        for (int j = 0; j < N; j++) {
            if ((level[j] == 1 || level[j] == 0) && visited[j] == 0) {
                if (first_printed) {
                    printf(", ");
                }
                printf("%d", j + 1);

                for (int k = 0; k < articulationSize; k++) {
                    if (articulationArray[k] == j) {
                        isArticulation = 1;
                        break;
                    }
                }

                if (!isArticulation) {
                    visited[j] = 1;
                }

                isArticulation = 0;
                first_printed = 1;
            }
        }
        printf("}");

        if (i != 0) { // Adiciona a vírgula entre componentes biconexas
            printf(", ");
        }
    }
    printf("\n");
}

// Função para identificar pontes
void bridges(int v, int visited[], int time[], int low[], int parent[], int disc[], int N) {
    static int t = 0;
    visited[v] = 1;
    disc[v] = low[v] = ++t;

    for (int i = 0; i < N; i++) {
        if (graph[v][i]) {
            int u = i;
            if (!visited[u]) {
                parent[u] = v;
                bridges(u, visited, time, low, parent, disc, N);
                low[v] = (low[u] < low[v]) ? low[u] : low[v];
                if (low[u] > disc[v]) {
                    printf("Bridge: (%d, %d)\n", v + 1, u + 1);
                    bridge = 1;
                }
            } else if (u != parent[v]) {
                low[v] = (disc[u] < low[v]) ? disc[u] : low[v];
            }
        }
    }
}

int main() {
    FILE* file = fopen("arquivo.txt", "r");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    int numberGraphs;
    fscanf(file, "%d", &numberGraphs);

    for (int k = 0; k < numberGraphs; k++) {
        int N, M;
        fscanf(file, "%d %d", &N, &M);

        initializeVariables(N);

        for (int i = 0; i < M; i++) {
            int u, v;
            fscanf(file, "%d %d", &u, &v);
            graph[u - 1][v - 1] = 1;
            graph[v - 1][u - 1] = 1;
        }

        // Transformar o grafo não dirigido em dirigido
        dfs(0, -1, N);

        // Printar Lowpoints
        printf("\nLowpoints: ");
        for (int i = 0; i < N; i++) {
            printf("%d:%d ", i + 1, low[i]);
        }
        printf("\n");

        // Articulações
        int articulationSize;
        int articulation[MAX_N];

        articulations(&articulationSize, N, articulation);

        printf("Articulations: ");
        if (articulationSize == 0) {
            printf("nenhuma");
        }
        for (int i = 0; i < articulationSize; i++) {
            printf("%d ", articulation[i] + 1);
        }
        printf("\n");

        int visited[MAX_N] = {0};
        int time[MAX_N];
        int disc[MAX_N];
        for (int i = 0; i < N; i++) {
            time[i] = -1;
            disc[i] = -1;
        }
        bridges(0, visited, time, low, parent, disc, N);
        if (!bridge) {
            printf("Bridge: nenhuma\n");
        }
        int markersSize;
        int markerss[MAX_N];

        markers(articulation, articulationSize, &markersSize, N, markerss);

        printf("Markers: ");
        for (int i = 0; i < markersSize; i++) {
            printf("%d ", markerss[i] + 1);
        }
        printf("\n");

        biconnectedComponents(markerss, markersSize, articulation, articulationSize, N);
    }

    fclose(file);

    return 0;
}
