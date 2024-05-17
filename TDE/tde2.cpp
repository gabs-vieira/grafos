#include <stdio.h>
#include <stdlib.h>

struct Aresta {
    int origem, destino, peso;
};


void bellmanFord( int N, int M, struct Aresta arestas[], int vertice_inicial, int vertice_final){

    int distancias[N]; 

    // Iniciarliazar todas as distâncias como infinito
    // A distância do vértice inicial é 0
    for(int i = 1; i <= N; i++){
        distancias[i] = 1000;
    }
    distancias[vertice_inicial] = 0;


    // Atualizando todas as arestas
    for(int i = 0; i < N ; i++){
        for(int j = 0; j < M; j++){
            
            int valor_origem = arestas[j].origem;
            int valor_destino = arestas[j].destino;
            int peso = arestas[j].peso;

            if( distancias[valor_origem] + peso < distancias[valor_destino] ){
                distancias[valor_destino] = distancias[valor_origem] + peso;
            }
        }
    }

    for(int j = 0; j < M; j++){
        int valor_origem = arestas[j].origem;
        int valor_destino = arestas[j].destino;
        int peso = arestas[j].peso;

        if( distancias[valor_origem] + peso < distancias[valor_destino] ){
            printf("O grafo tem ciclo de custo negativo\n");
            return;
        }
    }

    printf(" A distância do vértice %d ao vértice %d é %d.\n", vertice_inicial, vertice_final, distancias[vertice_final]);

}


int main(){

    FILE *arquivo;
    arquivo = fopen("entrada.txt", "r");

    int N, M; // N = n vertices; M = Arcos
    fscanf(arquivo, "%d %d", &N, &M);

    struct Aresta arestas[M];
    for(int i = 0; i< M; i++){
        fscanf(arquivo, "%d %d %d", &arestas[i].origem, &arestas[i].destino, &arestas[i].peso);
    }

    int Q; //Q = numero de consultas
    fscanf(arquivo, "%d", &Q);

    for(int i = 0; i< Q; i++){
        int x, y;
        fscanf(arquivo, "%d %d", &x, &y);

        bellmanFord( N, M, arestas, x, y);

    }

    fclose(arquivo);

    return 0;
}