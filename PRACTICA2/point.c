/* 
 * File:   point.h
 * Author: Alfonso y Luis
 *
 * Created on 11 de febrero de 2022, 18:30
 */



#include "types.h"
#include "point.h"



struct _Point{
int x, y;
char symbol;

Bool visited;
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
    p->visited = FALSE;

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

Bool point_getVisited (const Point *p){
    if(!p){
        return FALSE;
    }

    return p->visited; 
}

Status point_setVisited (Point *p, Bool bol){
    if(!p){
        return ERROR;
    }

    p->visited = bol;

    return OK;
}

Bool point_equal (const void *p1, const void *p2){
    int x1=0, x2=0, y1=0, y2=0, symb1='\0', symb2='\0';
    if(!p1 || !p2){
        return FALSE;
    }

    p1 = (Point*) p1;
    p2 = (Point*) p2;

    x1= point_getCoordinateX(p1);
    if(x1==INT_MAX){
        return FALSE;
    }
    x2= point_getCoordinateX(p2);
    if(x2==INT_MAX){
        return FALSE;
    }
    y1= point_getCoordinateY(p1);
    if(y1==INT_MAX){
        return FALSE;
    }
    y2= point_getCoordinateY(p2);
    if(y2==INT_MAX){
        return FALSE;
    }
    symb1= point_getSymbol(p1);
    if(symb1==CHAR_MAX){
        return FALSE;
    }
    symb2= point_getSymbol(p2);
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
    trg->visited=src->visited;

    return trg;
}

int point_print (FILE *pf, const void *p){
    int n=0; 
    const Point* pto = NULL;
    if(!pf || !p){
        return -1;
    }
    pto = point_hardcpy((const Point*)p);

    n = fprintf(pf,"[(%d,%d): %c]", point_getCoordinateX(pto), point_getCoordinateY(pto), point_getSymbol(pto));

    point_free((Point *)pto);
    return n;
}

Status point_euDistance (const Point *p1, const Point *p2, double *distance){
    if(!p1 || !p2 || !distance) return ERROR;

    *distance = sqrt(((p1->x) - (p2->x))*((p1->x) - (p2->x)) + ((p1->y) - (p2->y))*((p1->y) - (p2->y)));

    return OK;
}

int point_cmpEuDistance (const void *p1, const void *p2){
    
    double d1=0;
    double d2=0;

    Point *origin = NULL;
    origin = point_new(0,0,BARRIER);
    if(!p1 || !p2 || !origin) return INT_MIN;
    
    point_euDistance(p1,origin,&d1);
    point_euDistance(p2,origin,&d2);

    if(d1 < 0 || d2 < 0) {
        point_free(origin);
        return INT_MIN;   
    } 

    if (d1==d2){
        point_free(origin);
        return 0;
    }
    else if (d1<d2){
        point_free(origin);
        return -1;
    }
    else if (d1>d2){
        point_free(origin);
        return 1;
    }
    else{
        point_free(origin);
        return INT_MIN;
    }

    point_free(origin);
    return INT_MIN;
}