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
    
    point_print(stdout,p[0]);
    printf(" ");
    point_print(stdout,p[1]);
    printf("\n");

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

    printf("Creating p[2]: ");
    point_print(stdout,p[2]);
    printf("\n");

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

    printf("Modifying p[2]: ");
    point_print(stdout,p[2]);
    printf("\n");

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

    printf("Modifying p[3]: ");
    point_print(stdout,p[3]);
    printf("\n");

    for(i=0; i<4; i++){
        point_print(stdout,p[i]);
        point_free(p[i]);
    }
    printf("\n");

    return 0;
}