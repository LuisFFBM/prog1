#include "stack_fDoble.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "types.h"

#define INIT_CAPACITY 2 
#define FCT_CAPACITY 2 

struct _Stack{
    void **item; /*!<Dynamic array of elements*/
    int top; /*!<index of the top element in the stack*/
    int capacity; /*!<xcapacity of the stack*/
};

Stack * stack_init (){
    Stack *s = NULL;
    int i;

    s = (Stack*) malloc (sizeof(Stack));
    if(!s) return NULL;

    s->top=-1;
    s->capacity=INIT_CAPACITY;
 
    s->item = (void**) malloc (sizeof(void *));
    if(!(s->item)){
        free(s);
    }

    for(i=0;i<INIT_CAPACITY;i++){
        s->item[i]=NULL;

    }

    return s;

}


void * stack_pop (Stack *s){
    void *a;
    if(!s||stack_isEmpty(s)==TRUE) return NULL;

    a = s->item[s->top];
    s->item[s->top]=NULL;
    s->top--;

    return a;
}


void * stack_top (const Stack *s){
    if(!s||stack_isEmpty(s)==TRUE) return NULL;


    return s->item[s->top];
}


Bool stack_isEmpty (const Stack *s){
    if(!s) return TRUE;

    if(s->top==-1) return TRUE;
    
    return FALSE;
}

size_t stack_size (const Stack *s){
    if(!s) return 0;

    return (s->capacity);

}

int stack_print(FILE* fp, const Stack *s, P_stack_ele_print f){
    int i;

    if(!fp||!s||!f) return -1;

    for(i=0;i<=s->top;i++){
        f(fp,s->item[i]);

    }


    return 0;
}

