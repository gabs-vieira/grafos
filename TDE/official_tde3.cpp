#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100

int g[MAX_N][MAX_N];
int nivel[MAX_N];
int low[MAX_N];
int pai[MAX_N];
int filhos[MAX_N][MAX_N];
int num_filhos[MAX_N];
int ponte_encontrada;

void inicializar(int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            g[i][j] = 0;
        }
        nivel[i] = -1;
        low[i] = -1;
        pai[i] = -1;
        num_filhos[i] = 0;
    }
    ponte_encontrada = 0;
}

void marcar(int linha1, int linha2) {
    g[linha1][linha2] = 1;
    g[linha2][linha1] = 1;
}

void dfs(int v, int pai_atual, int N) {
    static int tempo = 0;
    nivel[v] = low[v] = ++tempo;
    pai[v] = pai_atual;

    for (int i = 0; i < N; i++) {
        if (g[v][i] == 1) {
            if (nivel[i] == -1) {
                filhos[v][num_filhos[v]++] = i;
                dfs(i, v, N);
                low[v] = (low[i] < low[v]) ? low[i] : low[v];
            } else if (i != pai_atual) {
                low[v] = (nivel[i] < low[v]) ? nivel[i] : low[v];
            }
        }
    }
}

int acharDemarcadores(int vetorArticulacao[], int tamanhoArticulacao, int *tam, int N, int vetor[]) {
    int n = 0;
    int i, j;
    for (i = 0; i < N; i++) {
        if (pai[i] == -1) {
            n += num_filhos[i];
        }
    }
    for (i = 0; i < tamanhoArticulacao; i++) {
        n += num_filhos[vetorArticulacao[i]];
    }

    int index = 0;

    for (i = 0; i < N; i++) {
        if (pai[i] == -1) {
            for (j = 0; j < num_filhos[i]; j++) {
                vetor[index++] = filhos[i][j];
            }
        }
    }
    for (i = 0; i < tamanhoArticulacao; i++) {
        for (j = 0; j < num_filhos[vetorArticulacao[i]]; j++) {
            vetor[index++] = filhos[vetorArticulacao[i]][j];
        }
    }
    *tam = n;
    return n;
}

int acharArticulacao(int *tam, int N, int vetor[]) {
    int n = 0;
    
    for (int i = 0; i < N; i++) {
        if (pai[i] == -1 && num_filhos[i] >= 2) {
            vetor[n++] = i;
        } else if (pai[i] != -1) {
            int isArticulacao = 0;
            for (int j = 0; j < num_filhos[i]; j++) {
                if (low[filhos[i][j]] >= nivel[i]) {
                    isArticulacao = 1;
                    break;
                }
            }
            if (isArticulacao) {
                vetor[n++] = i;
            }
        }
    }
    
    *tam = n;
    return n;
}

void bfs(int vi, int N) {
    int fila[MAX_N], PA = 0, TD = 0;
    fila[PA++] = vi;
    nivel[vi] = 0;

    while (TD < PA) {
        int v = fila[TD++];
        for (int i = 0; i < N; i++) {
            if (g[v][i] && nivel[i] == -1) {
                fila[PA++] = i;
                nivel[i] = nivel[v] + 1;
            }
        }
    }
}

void encontrarComponentesBiconexas(int demarcadores[], int tamDemarcadores, int vetorArticulacao[], int tamanhoArticulacao, int N) {
    int visitado[MAX_N];
    int ehArticulacao = 0;

    for (int i = 0; i < N; i++) {
        visitado[i] = 0;
        nivel[i] = -1;
    }

    printf("\n");
    printf("CB:\n");

    for (int i = tamDemarcadores - 1; i >= 0; i--) {
        for (int j = 0; j < N; j++) {
            nivel[j] = -1;
        }

        bfs(demarcadores[i], N);

        ehArticulacao = 0;

        for (int j = 0; j < N; j++) {
            if ((nivel[j] == 1 || nivel[j] == 0) && visitado[j] == 0) {
                printf("%d ", j + 1);

                for (int k = 0; k < tamanhoArticulacao; k++) {
                    if (vetorArticulacao[k] == j) {
                        ehArticulacao = 1;
                        break;
                    }
                }

                if (!ehArticulacao) {
                    visitado[j] = 1;
                }

                ehArticulacao = 0;
            }
        }

        printf("\n");
    }
}

void encontrarPontes(int v, int visitado[], int tempo[], int low[], int pai[], int disc[], int N) {
    static int t = 0;
    visitado[v] = 1;
    disc[v] = low[v] = ++t;

    for (int i = 0; i < N; i++) {
        if (g[v][i]) {
            int u = i;
            if (!visitado[u]) {
                pai[u] = v;
                encontrarPontes(u, visitado, tempo, low, pai, disc, N);
                low[v] = (low[u] < low[v]) ? low[u] : low[v];
                if (low[u] > disc[v]) {
                    printf("Ponte: (%d, %d)\n", v + 1, u + 1);
                    ponte_encontrada = 1;
                }
            } else if (u != pai[v]) {
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

    int quantidade_grafos;
    fscanf(file, "%d", &quantidade_grafos);
    
    for (int k = 0; k < quantidade_grafos; k++) {
        int N, M;
        fscanf(file, "%d %d", &N, &M);

        inicializar(N);
        
        for (int i = 0; i < M; i++) {
            int u, v;
            fscanf(file, "%d %d", &u, &v);
            marcar(u - 1, v - 1);
        }

        dfs(0, -1, N);
        printf("Grafo: %d\n", k + 1);
        printf("Lowpts:\n");
        for (int i = 0; i < N; i++) {
            printf("%d:%d\n", i + 1, low[i]);
        }
        printf("\n");

        int tamArticulacao;
        int articulacao[MAX_N];

        acharArticulacao(&tamArticulacao, N, articulacao);

        printf("Articulações: ");
        if(tamArticulacao == 0){
            printf("nenhuma");
        }
        for (int i = 0; i < tamArticulacao; i++) {
            printf("%d ", articulacao[i] + 1);
        }
        printf("\n");

        int visitado[MAX_N] = {0};
        int tempo[MAX_N];
        int disc[MAX_N];
        for (int i = 0; i < N; i++) {
            tempo[i] = -1;
            disc[i] = -1;
        }
        encontrarPontes(0, visitado, tempo, low, pai, disc, N);
        if (!ponte_encontrada) {
            printf("Ponte: nenhuma\n");
        }
        int tamDemarcadores;
        int demarcadores[MAX_N];

        acharDemarcadores(articulacao, tamArticulacao, &tamDemarcadores, N, demarcadores);

        printf("Demarcadores: ");
        for (int i = 0; i < tamDemarcadores; i++) {
            printf("%d ", demarcadores[i] + 1);
        }
        printf("\n");

        encontrarComponentesBiconexas(demarcadores, tamDemarcadores ,articulacao,tamArticulacao, N);
    }

    fclose(file);


    return 0;
}