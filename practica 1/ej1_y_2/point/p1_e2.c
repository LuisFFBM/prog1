/* 
 * File:   point.h
 * Author: Alfonso y Luis
 *
 * Created on 11 de febrero de 2022, 18:30
 */
#include <stdlib.h>
#include <stdio.h>
#include "point.h"
#include "map.h"


int main(){
    int i=0, j=0;
    unsigned int x=4,y=3;
    Map *map = NULL;
    Point *p = NULL;
    
    map = map_new(y,x);
    if(!map){
        return -1;
    }

    p = point_new(0,0,'.');
    if(!p){
        return -1;
    }

    for(i=0; i< map_getNcols(map); i++){
        for(j=0; j< map_getNrows(map); j++){
            
            point_setCoordinateX(p,i);
            point_setCoordinateY(p,j);
            point_setSymbol(p,'+');

            map_insertPoint(map, p);

            /*if(j == 1){
                if(i == 1){
                    map_setInput(map, p);
                }
                else if(i == 2){
                    map_setOutput(map, p);
                }
            }
            if(j == (map_getNrows(map) - 1) || j == 0){
                if(i == (map_getNcols(map) - 1) || i == 0){
                   point_setSymbol(p,'+'); 
                   map_insertPoint(map, p);
                }
                
            }
            else {
                point_setSymbol(p,'.');
                map_insertPoint(map, p);p = point_new(0,0,'.');
    if(!p){
        return -1;
    }

            }*/
                
        }
    }

    fprintf(stdout,"Map:\n");
    map_print(stdout,map);

    fprintf(stdout,"\n");

    fprintf(stdout,"Get output neighboors:\n");

    /*map_getNeighboor*/

    point_free(p);

    map_free(map);
    

    return 0;
}