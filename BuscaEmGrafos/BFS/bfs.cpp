//
// Created by gabriel on 27/03/24.
//

#define N 10

void bfs(int vi, int G[N][N], int nivel[N]){

    for (int i = 0; i < N; i++){ nivel[i] = -1; }

    nivel[vi] = 0;
    int NivelCorrente = 0;

    while(1){
        int trocou = 0;
        for (int i=0; i < N; i++){
            if (nivel[i] == NivelCorrente){
                for (int j = 0; j < N; j++){
                    if (G[i][j] == 1 && nivel[j] == -1){
                        nivel[j] = NivelCorrente + 1;
                        trocou = 1;
                    }
                }
            }
        }
        if (trocou == 0) break;
        NivelCorrente++;
    }

}