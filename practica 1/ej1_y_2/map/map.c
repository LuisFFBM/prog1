#include "map.h"





Map * map_new (unsigned int nrows,  unsigned int ncols){
    Map *mp=NULL;

    mp = (Map *) malloc (sizeof(Map));
    if (!mp){
       return NULL; 
    }

    mp->input = point_new(0,0,'i');
    mp-> output = point_new(0,0,'o');
    
    mp->nrows = nrows;
    mp->ncols = ncols;

    return mp;
}

void map_free (Map *mp){
    int i=0, j=0;
    if(!mp)
    {
        return;
    }
    
    for(i=0; i<mp->ncols; i++){
        for(j=0; j<mp->nrows; j++){
            free(mp->array[j][i]);
        }
    }
    point_free(mp->input);
    point_free(mp->output);
    free(mp);
}

Point *map_insertPoint (Map *mp, Point *p){
    if(!mp || !p){
        return NULL;
    }
    int x=0, y=0;

    x = point_getCoordinateX(p);
    y = point_getCoordinateY(p);
    

    mp->array[y][x] = p;

    return mp->array[y][x];
}

int map_getNcols (const Map *mp){
    if(!mp){
        return -1;
    }

    return mp->ncols;
}

int map_getNrows (const Map *mp){
    if(!mp){
        return -1;
    }

    return mp->nrows;
}

Point * map_getInput(const Map *mp){
    if(!mp){
        return NULL;
    }

    return mp->input;
}

Point * map_getOutput (const Map *mp){
    if(!mp){
        return NULL;
    }

    return mp->output;
}

Point *map_getPoint (const Map *mp, const Point *p){
    if(!mp || !p){
        return NULL;
    }

    int i = 0, j=0;

    for(i=0; i<mp->ncols; i++){
        for(j=0; j<mp->nrows; j++){
            if(mp->array[i][j] == p){
                return mp->array[i][j];
            }
        }
    }

    return NULL;
    
}

Point *map_getNeighboor(const Map *mp, const Point *p, Position pos){
    int x,y;

    if(!mp || !p){
        return NULL;
    }

    x = point_getCoordinateX(p);
    y = point_getCoordinateY(p);
    
    switch (pos){

        case RIGHT:
            return mp->array[y][x+1];
            break;
        
        case LEFT:
            return mp->array[y][x-1];
            break;
        
        case UP:
            return mp->array[y-1][x];
            break;

        case DOWN:
            return mp->array[y+1][x];
            break;

        case STAY:
            return mp->array[y][x];
            break;  

        default:
            return NULL;
            break;
    }



    return NULL;
}

Status map_setInput(Map *mp, Point *p){
    if(!p || !mp){
        return ERROR;
    }
    /*
    int x=0, y=0;

    x = point_getCoordinateX(p);
    y = point_getCoordinateY(p);

    if(ERROR == point_setSymbol(p,'i')){
        return ERROR;
    }

    */
    mp->input = p;
    return OK;
}

Status map_setOutput (Map *mp,Point *p){
    if(!p || !mp){
        return ERROR;
    }
    /*
    int x=0, y=0;

    x = point_getCoordinateX(p);
    y = point_getCoordinateY(p);

    if(ERROR == point_setSymbol(p,'o')){
        return ERROR;
    }

    
    mp->array[x][y] = p;*/
    mp->output = p;
    return OK;
}

int map_print(FILE*pf, Map *mp){
    int i=0, j=0, car=0, count=0;
    unsigned int max_col=0;
    unsigned int max_row=0;
    if(!pf || !mp){
        return -1;
    }

    
    max_col = map_getNcols(mp);
    max_row = map_getNrows(mp);

    count += fprintf(pf, "%d, %d\n", max_row, max_col);
    
    for(i=0; i< max_col; i++){
        for(j=0; j< max_row; j++){
            
            car = point_print(pf,(mp->array[j][i]));
            if(car == -1){
                return -1;
            }
            else{
                count+=car;
            }
        }
    }
    
    return count;
}

