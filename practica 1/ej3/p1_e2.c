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
    int i=0, j=0, n=0;
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

            
            if(j<= (map_getNrows(map)-1) && (i == 0 || i == (map_getNcols(map)-1))){
                point_setSymbol(p,BARRIER); 
                
            }
            else if(i<=(map_getNcols(map)-1) && (j == 0 || j == (map_getNrows(map)-1))){
                point_setSymbol(p,BARRIER); 
                
            }
            else if(j == 1){
                if(i == 1){
                    point_setSymbol(p,INPUT);
                    
                }
                else if(i == 2){
                    point_setSymbol(p,OUTPUT);
                    
                }
            }
            else {
                point_setSymbol(p,SPACE);
                

            }
            
            map->array[j][i] = point_hardcpy(map_insertPoint(map, p));
                
        }
    }
    
    fprintf(stdout,"Map:\n");

    n = map_print(stdout,map);
    if(n == -1){
        return -1;
    }
    fprintf(stdout,"\n");

    fprintf(stdout,"Get output neighboors:\n");

    for(i=RIGHT; i<STAY; i++){
        point_print(stdout,map_getNeighboor(map,map->array[1][1],i));
    }


    

    point_free(p);

    map_free(map);
    

    return 0;
}