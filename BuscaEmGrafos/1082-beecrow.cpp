#include <stdio.h>
#include <stdio.h>


int main(){

    int n; //quantidade de testes que vem a seguir
    scanf("%d", &n);

    for (int i =0; i<n;i++) {
        int v, e; //v = número de vértices, e = número de arestas
        char m[26][26] = {0}; //matriz de adjacência

        scanf("%d%d", &v, &e);

        for (int j = 0; j<e; j++){
            char a, b;
            scanf("%c%c", &a, &b);
            m[a-97][b-97] = 1; //   97 é o valor de 'a' na tabela ASCII
            m[b-97][a-97] = 1; //   97 é o valor de 'a' na tabela ASCII
        }


    }



    return 0;
}