// Caminho válido é aquele que passa por todos os vértices do grafo, sem repetir vértices, e que passa por todas as arestas do grafo, sem repetir arestas.
// Caminho euleriano é um caminho válido que começa e termina no mesmo vértice.
// Ciclo euleriano é um caminho euleriano que passa por todas as arestas do grafo.
// Um grafo é euleriano se possui um ciclo euleriano.

#include <stdio.h>


int main() {

    int n, m;  //n = número de vértices, m = número de arestas
    scanf("%d %d", &n, &m);

    int grau[n];  //grau de cada vértice (Grau é o número de arestas que incidem em um vértice)
    for(int i = 0; i < n; i++) grau[i] = -0; //inicializa o grau de cada vértice com 0 para sinalizar que cada grau não possui arestas

    //Lê as arestas e incrementa o grau de cada vértice
    for(int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        grau[a]++;
        grau[b]++;
    }

    //Verifica se o grafo é euleriano
    //se o garfo é euleriano então é um ciclo euleriano
    bool euleriano = true;
    for(int i = 0; i < n; i++) {
        if(grau[i] % 2 != 0) {
            euleriano = false;
            break;
        }
    }



//    a - "É um ciclo euleriano"
//    b - "É um caminho euleriano, mas não um ciclo"
//    c - "É um caminho válido, mas não euleriano"
//    d - "Não é um caminho válido"


}