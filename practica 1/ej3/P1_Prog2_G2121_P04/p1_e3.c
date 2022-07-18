/* 
 * File:  p1_e3
 * Author: Alfonso y Luis
 *
 * Created on 22 de febrero de 2022, 12:30
 */
#include <stdlib.h>
#include <stdio.h>
#include "point.h"
#include "map.h"

int main(int argc, char*argv[]){
    int i=0;
    FILE* pf = NULL;
    Map* map = NULL;

    if(argc != 2){
        return -1;
    }

    pf = fopen(argv[1], "r");
    if(!pf){
        return -1;
    }

    printf("Maze:\n");

    map = map_readFromFile(pf);
    if(!map){
        fclose(pf);
        return -1;
    }
    fclose(pf);

    map_print(stdout, map);

    printf("\n");

    printf("Get output neighboors:\n");

    for(i=0; i< STAY; i++){
        point_print(stdout,map_getNeighboor(map,map->output, i));
    }

    printf("\n");

    printf("Get right inferior corner neighboors:\n");
    
    for(i=0; i< STAY; i++){
        point_print(stdout,map_getNeighboor(map,map->array[map->nrows-1][map->ncols-1], i));
    }

    printf("\n");

    map_free(map);
    return 0;
}