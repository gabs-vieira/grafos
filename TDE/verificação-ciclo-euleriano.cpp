// Caminho Euleriano = Passar por todas as arestas sem repetir nenhuma
// Ciclo = Passar por todas as arestas terminar no mesmo vértice que começou

#include <stdio.h>

int main() {
    printf("Digite o número de vértices e arestas do grafo: \n");
    int N, M; // Número de vértices e arestas
    scanf("%d %d", &N, &M);

    int grafo[100][100] = {0}; // Inicializa o grafo com 0

    //Leitura do grafo
    for (int i = 0; i < M; i++) {
        int u, v;
        printf("Digite a aresta %d: \n", i + 1);
        scanf("%d %d", &u, &v);
        grafo[u][v] = 1;
        grafo[v][u] = 1;
    }

    int q; //quantidade de caminhos
    printf("Digite a quantidade de caminhos: \n");
    scanf("%d", &q);


    for(int j = 0; j < q; j++ ){

        int quantidadeVeritces;
        printf("Digite a quantidade de vértices do caminho %d: \n", j + 1);
        scanf("%d", &quantidadeVeritces);

        int caminho[100] = {0}; // Inicializa o caminho com 0
        for(int i = 0; i < quantidadeVeritces; i++){
            printf("Digite o vértice %d do caminho %d: \n", i + 1, j + 1);
            scanf("%d", &caminho[i]);
        }

        // [1,2,3,4,5,6,9....]
        int caminho_valido = 1;

        int controle[100][100]= {0};

        for (int i = 0; i < quantidadeVeritces - 1; i++){

            if( grafo[caminho[i]][caminho[i+1]] == 0){
                caminho_valido = 0;
                break;
            }

            //Soma quantas vezes está passando nas arestas
            controle[caminho[i]][caminho[i+1]] ++;
            controle[caminho[i+1]][caminho[i]] ++;
        }

        int caminho_euleriano = 1;
        //verifica se todas as arestas foram visitadas
        for (int i = 0; i < N; i++){
            for (int j = 0; j < N; j++){

                if(controle[i][j] + controle[j][i] > 2 ){
                    caminho_euleriano = 0;
                    break;
                }

            }
        }

        if(!caminho_valido) {
            printf("Caminho inválido\n");

        }else if(caminho_euleriano && caminho[0] == caminho[quantidadeVeritces - 1]){
            printf("É um ciclo euleriano\n");

        }else if(caminho_euleriano){
            printf("É um caminho euleriano\n");

        }else{
            printf("Caminho válido, mas não euleriano\n");
        }


    }


    return 0;
}
