/* 
 * File:   p2_e1c.c
 * Author: Luis
 *
 * Created on 6 march de 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include "point.h"
#include "stack_fDoble.h"

#define MAX_RAND 11
#define MAX_N 1500
#define MAX_POINTS 6
#define RETURN_ERROR -1
#define RETURN_OK 0

int int_cmp(const void *c1, const void *c2);
int print_ent(FILE* pf, const void* elem);

int main(int argc, char **argv){
    int n[MAX_N], i=0, n_points=0;
    Stack *s = NULL;
    Stack *ord = NULL;
    Status st = OK;
    srand(time(NULL));

    if(argc<2){
        n_points = MAX_POINTS;
    }
    else if(argc == 2){
        n_points = atoi(argv[1]);
        if(n_points<1 || n_points > MAX_N)
            return RETURN_ERROR;
    }
    else return RETURN_ERROR;
    
    s = stack_init();
    if(!s) return RETURN_ERROR;

    for(i=0; i<n_points; i++){
        n[i] = rand() % MAX_RAND;

        st = stack_push(s, &(n[i]));
        if(ERROR == st){
            stack_free(s);
            return RETURN_ERROR;
        }
    }

    fprintf(stdout, "original stack:\n");

    if(stack_print(stdout, s, print_ent) < 0){
        stack_free(s);
        return RETURN_ERROR;
    }
    
    ord = stack_order(s, int_cmp);
    if(!ord){
        stack_free(s);
        stack_free(ord);
        return RETURN_ERROR;
    } 

    fprintf(stdout, "ordered stack:\n");

    if(stack_print(stdout, ord, print_ent) < 0){
        stack_free(s);
        stack_free(ord);
        return RETURN_ERROR;
    }

    fprintf(stdout, "originial stack\n");

    if(stack_print(stdout, s, print_ent) < 0){
        stack_free(s);
        stack_free(ord);
        return RETURN_ERROR;
    }

    stack_free(s);
    stack_free(ord);


    return RETURN_OK;
}

int int_cmp(const void *c1, const void *c2) {
    if (!c1 || !c2)
        return INT_MIN;

    return (*((int *)c1) - *((int *)c2));
}

int print_ent(FILE* pf, const void* elem){
    if(!pf || !elem ) return RETURN_ERROR;

    return fprintf(pf, "%d", *((int*)(elem)));
     
}