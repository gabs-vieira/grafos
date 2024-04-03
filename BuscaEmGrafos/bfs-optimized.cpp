//
// Created by gabriel on 27/03/24.
//

#define N 10

int nivel[N];
int M[N][N];

void bfs(int vi){ //vi = vertice inicial

    int fila[1001];
    int PA =1; //Põe na fila
    int TD =0; //Tira da fila

    fila[0]=vi;
    nivel[vi]=0; //vetor global

    while(PA!=TD){
        int v = fila[TD++];
        for(int i=1; i <= n; i++){
            if( M[v][i] && nivel[i]==-1){
                fila[PA++]=i; //Põe na fila
                nivel[i]=nivel[v]+1; //vetor global
            }
        }
    }

}