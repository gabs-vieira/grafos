// Problem: 1923 - Beecrowd
// URL: http://www.urionlinejudge.com.br/judge/en/problems/view/1923
// Limits: 1s, 512 MB



#include <stdio.h>
#include <string.h>


char nomes[2000][100];
int pn = -1; //Flag p/ saber se o vertice ja foi visitado

int procurarNome( char nome[100] ){
    int i = 0;
    for(int i = 0; i <= pn && strcmp(nomes[i], nome) != 0; i++){ //
        if(i > pn){
            strcpy(nomes[++pn], nome);
            return pn;
        }else{
            return i;
        }
    }
}

void insere(tnodo **l, int n){

    tnodo *aux = (tnodo *)malloc(sizeof(tnodo));
    aux->prox=*l;
    aux->n=n;
    *l=aux;
    return;
}

char M[2000][2000]={0};


int main() {
    int n, G;
    scanf("%d%d", &n, &G);

    int nivel[] = {};

    for(int i =0;i<2*n; i++){
        nivel[i]=-1;
    }


    for(int i = 0; i<n; i++){

        char st1[100], st2[100];
        sscanf("%s%s", st1, st2);

        int a = procurarNome(st1), b = procurarNome(st2);

        M[b][a]= M[a][b]=1;

    }


    return 0;
}
