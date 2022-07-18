#include "node.h"


struct _Node {
void * info;
struct _Node * next ;
};

Node* node_new(){
    Node* nd=NULL;

    nd = (Node*) malloc (sizeof(Node));
    if(!nd) return NULL;

    nd->info=NULL;
    nd->next=NULL;

    return nd;
}

Status node_destroy(Node* nd){
    if (!nd) return ERROR;

    free(nd);
    nd = NULL;

    return OK;
}

Status node_set_info(Node* nd, void* ele){
    if(!nd||!ele) return ERROR;

    nd->info=ele;

    return OK;
}

void* node_get_info(Node* nd){
    if(!nd) return NULL;

    return nd->info;
}


Status node_set_next(Node* nd, Node* next){
    if(!nd||!next) return ERROR;

    nd->next=next;

    return OK;
}

Node* node_get_next(Node* nd){
    if(!nd) return NULL;

    return nd->next;
}
