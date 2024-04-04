#include <stdio.h>
#define n 9

void bfs( int M[n][n], int nivel[n], int vi){

    int fila[n];
    fila[0] = vi;

    int head = 0;
    int tail = 1;

    nivel[vi] = 0;

    while(head != tail){ // Enquanto a fila não estiver vazia
        int v = fila[head++];
        printf("%d\n", v);
        for(int i = 0; i < n; i++){
            if( M[v][i] == 1 && nivel[i] == -1){
                nivel[i] = nivel[v] + 1;
                fila[tail++] = i;
            }
        }
    }

}


int main(){

    int M[n][n]= {
        {0, 1, 0, 1, 0, 0, 0, 0, 0},
        {1, 0, 1, 0, 1, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 1, 0, 0, 0},
        {1, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 1, 0}
    };

    int nivel[n] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};

    bfs(M, nivel, 0);

    return 0;
}