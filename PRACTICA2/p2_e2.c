/* 
 * File:   p2_e2.c
 * Author: Alfonso y Luis
 *
 * Created on 12 march de 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "map.h"

int main(int argc, char *argv[]){

    Map* mp=NULL;
    FILE* pf=NULL;
    
    if(argc != 2) return -1;

    pf = fopen(argv[1], "r");
    if(!pf) return -1;

    mp = map_readFromFile(pf);
    if(!mp){
        map_free(mp);
        fclose(pf);
        return -1;
    }

    map_print(stdout,mp);
    
    fprintf(stdout, "\n");
 printf( "DFS traverse: \n");
  
    map_dfs(pf,mp);
    

    fclose(pf);
    map_free(mp);
    return 0;
}

