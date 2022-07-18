/* 
 * File:   p2_e1b.c
 * Author: Alfonso 
 *
 * Created on 5 march de 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include "point.h"
#include "stack_fDoble.h"

#define MAX_RAND 11
#define MAX_POINTS 6
#define MAX_N 7
#define RETURN_ERROR -1
#define RETURN_OK 0

int main_free(Point **p,int n, Stack* s, int error);

int main(int argc, char **argv){
    int i, n_points;
    double dist;
    Point* p[MAX_POINTS];
    Point* origen=NULL;
    Stack* s=NULL;
    Stack* ord=NULL;
    srand(time(NULL));

    if(argc < 2){
        n_points = MAX_POINTS;
    }
    else if(argc == 2){
        n_points = atoi(argv[1]);
        if(n_points<1 || n_points > MAX_N)
            return RETURN_ERROR;

    }
    else return RETURN_ERROR;
    
    origen=point_new(0,0,BARRIER);
    if(!origen) return RETURN_ERROR;

    s=stack_init();
    if(!s){
        point_free(origen);
        return RETURN_ERROR;
    }
    

    for(i=0;i<n_points;i++){
        p[i]=point_new(rand() %MAX_RAND,rand() %MAX_RAND, BARRIER);
        if(!p[i]){
            point_free(origen);
            main_free(p,i, s, RETURN_ERROR);
        }
        
        stack_push(s,p[i]);

        fprintf(stdout,"Point p[%d]=",i);
        point_print(stdout,p[i]);

        point_euDistance(p[i],origen,&dist);
        fprintf(stdout," distance: %f\n",dist);
    }
    
    fprintf(stdout,"original stack:\n");
    stack_print(stdout,s,point_print); 

    ord = stack_orderPoints(s);
    if(!ord){
        point_free(origen);
        stack_free(ord);
        main_free(p,n_points, s, RETURN_ERROR);
    }

    fprintf(stdout,"ordered stack:\n");
    stack_print(stdout,ord,point_print);

    fprintf(stdout,"original stack\n");
    stack_print(stdout,s,point_print);
    

    stack_free(ord);
    point_free(origen);
    main_free(p,n_points, s, RETURN_OK);

    return RETURN_OK;
}

int main_free(Point **p,int n, Stack* s, int error){
    int i=0;
    if(error == RETURN_ERROR){
        for(i=0; i<n; i++ ){
            point_free(p[i]);
        }
        stack_free(s);
        return -1;
    }
    else{
        for(i=0; i<n; i++ ){
            point_free(p[i]);
        }
        stack_free(s);
        return 0;
    }
    
}