/* 
 * File:   point.h
 * Author: Alfonso y Luis
 *
 * Created on 11 de febrero de 2022, 18:30
 */
#include <stdlib.h>
#include <stdio.h>
#include "point.h"

int main(){
    int i;
    Point *p[4];
    Bool iguales=FALSE;
    
    for(i=0; i<4; i++){
        p[i]=NULL;
    }

    p[0]=point_new(0,0,BARRIER);
    p[1]=point_new(0,1,BARRIER);

    if(!p[0] || !p[1]){
        return 1;
    }
    
    printf("[(%d, %d): %c] ", point_getCoordinateX(p[0]), point_getCoordinateY(p[0]), point_getSymbol(p[0]));
    printf("[(%d, %d): %c]\n", point_getCoordinateX(p[1]), point_getCoordinateY(p[1]), point_getSymbol(p[1]));

    iguales=point_equal(p[0],p[1]);
    
    printf("Equal points p[0] and p[1]?");

    if(iguales==TRUE){
        printf(" Yes\n");
        return 1;
    }
    if(iguales==FALSE){
        printf(" No\n");
    }

    p[2] = point_hardcpy(p[0]);

    if(!p[2]){
        return 1;
    }

    printf("Creating p[2]: [(%d, %d): %c]\n", point_getCoordinateX(p[2]), point_getCoordinateY(p[2]), point_getSymbol(p[2]));

    iguales=FALSE;

    iguales=point_equal(p[0],p[2]);
    
    printf("Equal points p[0] and p[2]?");

    if(iguales==TRUE){
        printf(" Yes\n");
    }
    if(iguales==FALSE){
        printf(" No\n");
        return 1;
    }

    if(point_setSymbol(p[2], SPACE) == ERROR){
        return 1;
    }

    printf("Modifying p[2]: [(%d, %d): %c]\n", point_getCoordinateX(p[2]), point_getCoordinateY(p[2]), point_getSymbol(p[2]));

    iguales=FALSE;

    iguales=point_equal(p[0],p[2]);
    
    printf("Equal points p[0] and p[2]?");

    if(iguales==TRUE){
        printf(" Yes\n");
        return 1;
    }
    if(iguales==FALSE){
        printf(" No\n");
    }

    p[3] = point_hardcpy(p[0]);

    if(!p[3]){
        return 1;
    }

    printf("Assign p[3] = p[0]\n");

    if(point_setSymbol(p[3], OUTPUT) == ERROR){
        return 1;
    }

    printf("Modifying p[3]: [(%d, %d): %c]\n", point_getCoordinateX(p[3]), point_getCoordinateY(p[3]), point_getSymbol(p[3]));

    printf("[(%d,%d): %c][(%d,%d): %c][(%d,%d): %c][(%d,%d): %c]",point_getCoordinateX(p[0]), point_getCoordinateY(p[0]), point_getSymbol(p[0]),point_getCoordinateX(p[1]), point_getCoordinateY(p[1]), point_getSymbol(p[1]),point_getCoordinateX(p[2]), point_getCoordinateY(p[2]), point_getSymbol(p[2]),point_getCoordinateX(p[3]), point_getCoordinateY(p[3]), point_getSymbol(p[3]));
    
    return 0;
}