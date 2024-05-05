#include <stdio.h>
#include <stdbool.h>



void dfs(int u ){

  if ( !visited[u] ){
    printf("%d", u);
    
    visited[u] = true;

    for(int v = 1; v <= n; v++){

      if( a[u][v] == 1 && visited[v] !== 0 ){
        dfs(v);
      }

    }

  }

}


int main(){

  
  return 0;
}