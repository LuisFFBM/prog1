/* 
 * File:    stack_fDoble.c
 * Author:  Alfonso & Luis
 *
 * Created on 5 march de 2022
 */

#include <stdlib.h>
#include <stdio.h>
#include "stack_fDoble.h"
#include "point.h"
#include "types.h"

#define INIT_CAPACITY 2 // init stack capacity
#define FCT_CAPACITY 2 // multiply the stack capacity

struct _Stack {

    void **item;    /*!<Dynamic array of elements*/
    int top;        /*!<index of the top element in the stack*/
    int capacity;   /*!<xcapacity of the stack*/
};

/* 
 * Author: Luis
 *
 * Created on 15 march de 2022
 */
void stack_free (Stack *s){
    int i=0, cap=0;
    if(!s) return;
    
    cap = (s->capacity-1);
    s->capacity = 0;

    for(i=0; i < cap; i++){
        s->item[i] = NULL;
        s->top--;
    }

    free(s->item);
    free(s);
}

/* 
 * Author: Luis
 *
 * Created on 15 march de 2022
 */
Status stack_push (Stack *s, const void *ele){
    
    if(!s || !ele) return ERROR;

    if((s->top+1) == s->capacity && stack_isEmpty(s) == FALSE){
        
    }
}

/* 
 * Author: Alfonso
 *
 * Created on 4 march de 2022
 */
Stack *stack_orderPoints (Stack *sin){
    Status st = OK;
    Stack *ord=NULL;
    Point *p=NULL, *p_aux = NULL;

    if(!sin) return NULL;

    ord = stack_init();
    
    if(!ord) return NULL;

    if(stack_isEmpty(sin)==TRUE) return NULL;
    
    while (stack_isEmpty(sin)==FALSE)
    {
        p = stack_pop(sin);
        if(!p) return NULL;

        while (stack_isEmpty(ord)==FALSE && point_cmpEuDistance(p, stack_top(ord)) < 0)
        {   
            p_aux = stack_pop(ord);
            stack_push(sin,p_aux);
        }
        
        st = stack_push(ord,p);
        if(st == ERROR) return NULL;

    }

    return ord;
}

/* 
 * Author: Luis
 *
 * Created on 5 march de 2022
 */

Stack *stack_order (Stack *s, int (*f_cmp)(const void *, const void *)){

    Stack *ord=NULL;
    void *p = NULL, *p_aux=NULL;

    if(!s || !f_cmp) return NULL;

    ord = stack_init();
    if(!ord) return NULL;

    if(stack_isEmpty(s)==TRUE){
        stack_free(ord);
        return NULL;
    }
    
    while (stack_isEmpty(s)==FALSE)
    {
        p = stack_pop(s);
        if(!p) return NULL;

        while (stack_isEmpty(ord)==FALSE && (*f_cmp)(p, stack_top(ord)) < 0)
        {
            p_aux = stack_pop(ord);
            stack_push(s,p_aux);
        }
        
        stack_push(ord,p);

    }

    return ord;
}