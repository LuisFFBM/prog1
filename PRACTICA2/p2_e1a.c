/* 
 * File:   p2_e1a.c
 * Author: Luis
 *
 * Created on 4 march de 2022
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "point.h"


#define MAX_RAND 11
#define NPOINTS 5

int main(){
    Point *p[NPOINTS];
    Point *origen=NULL;
    int x=0, y=0, i=0, j=0;
    double distance=0;

    srand(time(NULL));

    origen = point_new(0,0,BARRIER);

   

    for(i=0;i<NPOINTS; i++){

        x = (rand()%MAX_RAND);
        y = (rand()%MAX_RAND);

        p[i] = point_new(x,y,BARRIER);  
        if(!p[i]) return -1;

        printf("Point p[%d]=", i);
        point_print(stdout, p[i]);

        point_euDistance(origen, p[i], &distance);
        printf(" distance: %lf \n", distance);
  
    }

    for(i=0;i<NPOINTS; i++){
        for(j=i; j<NPOINTS; j++){
            printf("p[%d] < p[%d]: ", i, j);
            if(point_cmpEuDistance(p[i], p[j]) < 0) printf("True\n");
            else 
                printf("False\n");
        }
    }

    for(i=0; i<NPOINTS; i++){
        point_free(p[i]);
    }
    point_free(origen);
    return 0;
}

