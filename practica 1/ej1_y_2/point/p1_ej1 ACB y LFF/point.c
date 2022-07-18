/* 
 * File:   point.h
 * Author: Alfonso y Luis
 *
 * Created on 11 de febrero de 2022, 18:30
 */

#include <limits.h>
#include "types.h"
#include "point.h"


struct _Point{
int x, y;
char symbol;
};

Point * point_new (int x, int y, char symbol){

    Point *p=NULL;

    p = (Point *) malloc(sizeof(Point));
    
    if(p==NULL){
        return NULL;
    }

    p->x = x;
    p->y = y;
    p->symbol = symbol;

    return p;   
}

void point_free (Point *p){
    free (p);
}

int point_getCoordinateX (const Point *p){
    int x;

    if(p == NULL){
        return INT_MAX;
    }

    x = p->x;

    return x;
}

int point_getCoordinateY (const Point *p) {
    int y;

    if(p == NULL){
        return INT_MAX;
    }
    
    y = p->y;

    return y;   
}

char point_getSymbol (const Point *p) {
    char symbol;

    if(p == NULL){
        return CHAR_MAX;
    }
    
    symbol = p->symbol;
        
    return symbol;        
}

Status point_setCoordinateX (Point *p, int x){
    if(p==NULL){
        return ERROR;
    }

    p->x = x;

    return OK;
}

Status point_setCoordinateY (Point *p, int y){
    if(p==NULL){
        return ERROR;
    }

    p->y = y;

    return OK;
} 

Status  point_setSymbol (Point *p, char c) {
    if(p == NULL){
        return ERROR;
    }

    p->symbol = c;

    return OK;
}

Bool point_equal (const void *p1, const void *p2){
    if(p1==NULL || p2==NULL){
        return FALSE;
    }

    p1 = (Point*) p1;
    p2 = (Point*) p2;

    int x1= point_getCoordinateX(p1);
    if(x1==INT_MAX){
        return FALSE;
    }
    int x2= point_getCoordinateX(p2);
    if(x2==INT_MAX){
        return FALSE;
    }
    int y1= point_getCoordinateY(p1);
    if(y1==INT_MAX){
        return FALSE;
    }
    int y2= point_getCoordinateY(p2);
    if(y2==INT_MAX){
        return FALSE;
    }
    char symb1= point_getSymbol(p1);
    if(symb1==CHAR_MAX){
        return FALSE;
    }
    char symb2= point_getSymbol(p2);
    if(symb2==CHAR_MAX){
        return FALSE;
    }

    if (x1==x2){
        if(y1==y2){
            if(symb1==symb2){
                return TRUE;
            }
            else 
                return FALSE;
        }
        else 
            return FALSE;
    }
    
    return FALSE;  
}

Point *point_hardcpy (const Point *src) {
    Point *trg=NULL;

    if (!src)
        return NULL;

    trg = (Point *) malloc (sizeof(Point));
    if (!trg)
        return NULL;

    trg->x = src->x;
    trg->y = src->y;
    trg->symbol = src->symbol;

    return trg;
}
