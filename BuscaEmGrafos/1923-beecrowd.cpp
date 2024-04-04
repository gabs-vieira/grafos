// Problem: 1923 - Beecrowd
// URL: http://www.urionlinejudge.com.br/judge/en/problems/view/1923
// Limits: 1s, 512 MB

#include <stdio.h>
#include <string.h>



char M[2000][2000]={0};

int main() {
    int n, G;
    scanf("%d%d", &n, &G);

    char *names[n][100];
    for (int i = 0; i < n; i++){
        char name1, name2;
        scanf("%s%s", name1, name2);
        strcpy(names[i], name1);
        strcpy(names[i], name2);
    }



    return 0;
}
