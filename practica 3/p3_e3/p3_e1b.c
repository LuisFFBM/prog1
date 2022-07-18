#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "point.h"
#include "sorted_queue.h"

#define MAX_PTS 10
#define WORD 6
#define MAX_INTS 10
#define MAX_RAND 20
#define MAX_WORDS 5
#define MAX_CHAR 26
#define NOT_ORDER -1



/*function to check the order of the elements in the sorted queue*/
int test_order(Queue *q, p_queue_ele_cmp pccmp, p_queue_ele_print pcprint);

/*functions for the use of squeue prime functions with int queue */
int int_print(FILE *f, const void *x) {
  int *z = (int *) x;
  return fprintf(f, "%d ", *z);
}

int int_cmp(const void *n1, const void *n2){
    return (*((int*)n1) - *((int*)n2));
}


/*functions for the use of squeue prime functions with string queue*/
int str_print(FILE *f, const void *x) {
  char *z = (char *) x;
  return fprintf(f, "%s ", z);
}

int string_cmp(const void *s1, const void *s2) {
    return strcmp((char *)s1, (char *)s2); 
}

int main(){

    Queue *q_int = NULL;
    Queue *q_str = NULL;
    Queue *q_pt = NULL;
    Status st = OK;
    Point *p[MAX_PTS], *p_ref=NULL;
    int i = 0, j = 0, test=0, x=0, y=0;
    int n[MAX_INTS];
    char str[MAX_WORDS][WORD];
    srand(time(NULL));
    


    q_int = squeue_new();
    if(!q_int) return -1;

    q_str = squeue_new();
    if(!q_str) {
        squeue_free(q_int);
        return -1;
    }

    q_pt = squeue_new();
    if(!q_str) {
        squeue_free(q_int);
        squeue_free(q_str);
        return -1;
    }

    /*fill the array with random numbers*/
    for(i=0; i<MAX_INTS; i++){
        
        n[i] = rand() % MAX_RAND;
    }
    
    /*fill each string with random letters*/
    for(j=0; j<MAX_WORDS; j++){

        for(i=0; i<(WORD-1); i++){
        
            str[j][i] = (char)((rand() % MAX_CHAR) + 'a');
        }
        str[j][i] = '\0';
    }
    /*fill each point with random coordenates*/
    for(i=0;i<MAX_PTS; i++){

        x = (rand()%MAX_RAND);
        y = (rand()%MAX_RAND);

        p[i] = point_new(x,y,BARRIER);  
        if(!p[i]) {
            for(j = i; j >= 0; j--){
                point_free(p[j]);
            }
            squeue_free(q_int);
            squeue_free(q_str);
            squeue_free(q_pt);
            point_free(p_ref);
            return -1;
        }
    }
    
    fprintf(stdout, "----------------------------------------------------------------------\n");
    fprintf(stdout, "INT TEST:\n");
    fprintf(stdout, "----------------------------------------------------------------------\n");
    
    /*fills int queue and error control*/
    for(i=0; i< MAX_INTS && st == OK; i++){
        st = squeue_push(q_int, &(n[i]), int_cmp);
    }

    if(st == ERROR){
        fprintf(stdout, "Original int queue: ERROR\n");   
    } 
    else if( st == OK){
        fprintf(stdout, "Original int queue: OK\n");
        fprintf(stdout, "Queue size: %d \n", (int)squeue_size(q_int));
        squeue_print(stdout,q_int, int_print);   
    }
    test = test_order(q_int, int_cmp, int_print);
    if(test != NOT_ORDER){
        fprintf(stdout, "There were %d elements in the queue\n", test);
        squeue_print(stdout, q_int, int_print);
    }
    else{
        fprintf(stdout, "ERROR, the squeue is not ordered");
        squeue_print(stdout, q_int, int_print);
    }
    fprintf(stdout, "----------------------------------------------------------------------\n");
    fprintf(stdout, "STRING TEST:\n");
    fprintf(stdout, "----------------------------------------------------------------------\n");
    /*fills string queue and error control*/
    for(i=0; i< MAX_WORDS && st == OK; i++){
        st = squeue_push(q_str, str[i], int_cmp);
    }

    if(st == ERROR){
        fprintf(stdout, "Original string queue: ERROR\n");   
    } 
    else if( st == OK){
        fprintf(stdout, "Original string queue: OK\n");
        fprintf(stdout, "Queue size: %d \n", (int)squeue_size(q_str));
        squeue_print(stdout,q_str, str_print);   
    }
    test = test_order(q_str, string_cmp, str_print);
    if(test != NOT_ORDER){
        fprintf(stdout, "There were %d elements in the queue\n", test);
        squeue_print(stdout, q_str, str_print);
    }
    else{
        fprintf(stdout, "ERROR, the squeue is not ordered");
        squeue_print(stdout, q_str, str_print);
    }

    fprintf(stdout, "----------------------------------------------------------------------\n");
    fprintf(stdout, "POINT TEST:\n");
    fprintf(stdout, "----------------------------------------------------------------------\n");
    /*fills point queue and error control*/
    for(i=0; i< MAX_WORDS && st == OK; i++){
        st = squeue_push(q_pt, p[i], point_cmpEuDistance);
    }

    if(st == ERROR){
        fprintf(stdout, "Original points queue: ERROR\n");   
    } 
    else if( st == OK){
        fprintf(stdout, "Original points queue: OK\n");
        fprintf(stdout, "Queue size: %d \n", (int)squeue_size(q_pt));
        squeue_print(stdout,q_pt, point_print);   
    }
    test = test_order(q_pt, point_cmpEuDistance, point_print);
    if(test != NOT_ORDER){
        fprintf(stdout, "SUCCESS, the %d elements in the queue where order\n", test);
        squeue_print(stdout, q_pt, point_print);
    }
    else{
        fprintf(stdout, "ERROR, the squeue is not ordered");
        squeue_print(stdout, q_int, point_print);
    }
    
    

    squeue_free(q_pt);
    squeue_free(q_str);
    squeue_free(q_int);
    for(i=0; i< MAX_PTS; i++){
        point_free(p[i]);
    }
    
    return 0;
}

int test_order(Queue *q, p_queue_ele_cmp pccmp, p_queue_ele_print pcprint) {
    Status st = OK;
    void *n1 = NULL, *n2 = NULL, *n_aux = NULL;
    int i = 0, size = 0;

    if(!q || !pccmp || !pcprint) return NOT_ORDER;

    size = queue_size(q);

    n1 = squeue_pop(q); 
    if(!n1) st = ERROR;

    for(i=0; i < (size-1) && st == OK ; i++){
        
        n2 = squeue_pop(q);
        if(!n2) st = ERROR;
        else{
            if(pccmp(n1,n2) > 0 ) i = (size-1);
            n1 = n2;   
        }
        
    }
    if(st == OK){
        if(i != (size-1)){
            for(i=0; squeue_isEmpty(q) == FALSE && i<size; i++){
                n_aux = squeue_pop(q);
            }
            fprintf(stdout, "Queue is in order and empty:\n");
            fprintf(stdout, "Queue size: %d\n", (int)squeue_size(q));
            squeue_print(stdout,q, pcprint);
            return size;
        }
        else{
            for(i=0; squeue_isEmpty(q) == FALSE && i<size; i++){
                n_aux = squeue_pop(q);
            }
        }
        
    }
    else if(st == ERROR){
        
        
        for(i=0; n_aux  && i<size; i++){
            n_aux = squeue_pop(q);
        }
        fprintf(stdout, "Queue size: %d\n", (int)squeue_size(q));
        squeue_print(stdout,q, pcprint);
        
        
    }

    return NOT_ORDER;
}
