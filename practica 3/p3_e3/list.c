/* 
 * File:   list.c
 * Author: Luis
 *
 * Created on 5 de april de 2022, 11:50
 */

#include "list.h"

struct _List {
    Node * first ;
    Node * last ;
};

List *list_new() {

    List *pl = NULL;

    pl = (List*) malloc (sizeof(List));

    if ( !pl ){
        return NULL;
    }

    pl->first = NULL;
    pl->last = NULL;
    
    return pl;
}

Status list_destroy(List* pl){
    Node* pn=NULL;

    if(!pl) return ERROR;

    while(pl->first!=NULL){
        pn=pl->first;
        pl->first=node_get_next(pn); /*pl->first=pn->next*/
        node_free(pn);
    }


    free(pl);

    return OK;
}

Bool list_isEmpty ( const List * pl ) {
    if ( !pl ){
        return TRUE ;
    }
    if ( !pl->first || !pl->last){
        return TRUE ;
    }
    return FALSE ;
}

Status list_pushFront ( List * pl , const void * e ) {
    Node * pn = NULL ;
    if ( !pl || !e ) {
        return ERROR ;
    }
    pn = node_new();
    if ( !pn){
        return ERROR ;
    }

    if(list_isEmpty(pl) == TRUE){
        node_set_info(pn, (void*)e);
        node_set_next(pn,pl->first);
        pl -> first = pn;
        pl->last = pn;
    }
    else{
        node_set_info(pn, (void*)e);
        node_set_next(pn,pl->first);
        pl -> first = pn ;
    }
    

    return OK ;
}

Status list_pushBack(List *pl, const void *e){
    if(pl||!e) return ERROR;

    Node* nd=NULL;
    Status st=OK;

    nd = node_new();
    if(!nd) return ERROR;

    st = node_set_info(nd,e);

    node_set_next(pl->last,nd);

    pl->last=nd;

    return st;
}

void * list_popFront ( List * pl ) {
    Node *pn = NULL;
    void *pe = NULL;
    if (list_isEmpty(pl)==TRUE) {
        return NULL;
    }
    
    pn = pl -> first ;
    pe = pn -> info ; /* Equivalently : pe = pl - > first - > info */
    pl - > first = pn - > next ;
    free ( pn ) ;
    return pe ;
}