#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "map.h"

int main(int argc, char *argv[]){
    Map* mp=NULL;
    FILE* pf=NULL;
    /*Point* p_aux=NULL;*/


    if(argc != 2) return -1;

    pf = fopen(argv[1], "r");
    if(!pf) return -1;

    mp = map_readFromFile(pf);
    if(!mp){
        map_free(mp);
        fclose(pf);
        return -1;
    }

    fprintf(stdout, "Maze:\n");

    map_print(stdout,mp);

    fprintf(stdout,"\n");

    fprintf(stdout,"BFS:\n");

    map_dfs(stdout,mp);

    fprintf(stdout,"\n");
    
    map_free(mp);
    fclose(pf);
    return 0;
}
