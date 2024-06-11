#include <stdio.h>
#include <stdbool.h>

/*
    O algoritmo de Prim trabalha com o Minimum Spinning Tree MST que é o menor caminho percorrido em um grafo.
    O grafo tem pesos em suas arestas.

    MST = subconjunto de arestas de menor peso que manteḿ o grafo conexo
*/

#define V 5 // Número de vértices no grafo
#define INF 1000 // Número de vértices no grafo


void primMST( int matriz[V][V], int vi ){

    int MST[V]; // Para armazenar a MST construída  [1, 5, 4, 6, 8]
    int key[V]; // Chaves usadas para escolher o mínimo peso da aresta no corte
    bool vert_incluidos[V]; // Vértices incluidos na MST

    //Atualiza todas as keys = distâncias em infinitos 
    for(int i = 0; i < V; i++ ){
        key[i] = INF;
        vert_incluidos[i]= false;
    }
    
    key[vi] = 0;
    MST[vi] = vi;


    for(int i = 0; i < V; i++ ){

        //Encontrar o menor valor dentre aqueles que ainda não foram incluidos

        int u = INF;
        int vertice;
        
        for(int k = 0; k < V; k++){

            if( key[k]  < u  &&  !vert_incluidos[k] ){
                vertice = k;
                u = key[k];
            }
        }
        
        vert_incluidos[vertice] = true;


        //Atualiza as distâncias dos vertes adjacentes (Relaxamento) 
        for(int j = 0; j < V; j++){
            if( !vert_incluidos[j] && key[j] > matriz[vertice][j]  ){
                key[j] = matriz[vertice][j];
                MST[j] = vertice;
            }
        }

    }


    // Imprime a MST
    printf("Aresta   Peso\n");
    for (int i = 1; i < V; i++)
        printf("%d - %d    %d \n", parent[i], i, graph[i][parent[i]]);


}



int main (){

    // Grafo com os pesos de cada aresta para serem percorridas.
    int graph[V][V] = {
        { 0, 2, 0, 6, 0 },
        { 2, 0, 3, 8, 5 },
        { 0, 3, 0, 0, 7 },
        { 6, 8, 0, 0, 9 },
        { 0, 5, 7, 9, 0 }
    };

    int vi;
    scanf("%d", &vi); //Vertice inicial 

    primMST(graph, vi);


    return 0;
}