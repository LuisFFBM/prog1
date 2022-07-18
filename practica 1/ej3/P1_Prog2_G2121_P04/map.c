/* 
 * File:  map.c
 * Author: Alfonso y Luis
 *
 * Created on 11 de febrero de 2022, 12:30
 */

#include "map.h"


Map * map_new (unsigned int nrows,  unsigned int ncols){
   /* int i=0, j=0;*/
   
    Map *mp=NULL;
    

    mp = (Map *) malloc (sizeof(Map));
    if (!mp){
       return NULL; 
    }

    mp->input = point_new(0,0,'i');
    mp-> output = point_new(0,0,'o');
    
    mp->nrows = nrows;
    mp->ncols = ncols;

    /*for(i=0; i<mp->ncols; i++){
        for(j=0; j<mp->nrows; j++){
            mp->array[j][i] = point_new(i,j,'\0');
        }
    }*/

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
            point_free(mp->array[j][i]);
        }
    }
    point_free(mp->input);
    point_free(mp->output);
    free(mp);
}

Point *map_insertPoint (Map *mp, Point *p){
    int x=0, y=0;
    
    if(!mp || !p){
        return NULL;
    }

    x = point_getCoordinateX(p);
    y = point_getCoordinateY(p);
    

    mp->array[x][y] = p;

    return mp->array[x][y];
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
    int i = 0, j=0;
    
    if(!mp || !p){
        return NULL;
    }

    for(i=0; i<mp->ncols; i++){
        for(j=0; j<mp->nrows; j++){
            if(mp->array[j][i] == p){
                return mp->array[j][i];
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
            if(x == mp->ncols - 1) break;
            if(mp->array[y][x+1] == NULL) break;
            return mp->array[y][x+1];
            break;
        
        case LEFT:
            if(x == 0) break;
            if(mp->array[y][x-1] == NULL) break;
            return mp->array[y][x-1];
            break;
        
        case UP:
            if(y == 0) break;
            if(mp->array[y-1][x] == NULL) break;
            return mp->array[y-1][x];
            break;

        case DOWN:
            if(y == mp->nrows - 1) break;
            if(mp->array[y+1][x] == NULL) break;
            return mp->array[y+1][x];
            break;

        case STAY:
            
            if(mp->array[y][x] == NULL) break;
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
    
    int x=0, y=0;

    x = point_getCoordinateX(p);
    y = point_getCoordinateY(p);
    if(ERROR == point_setCoordinateX(mp->input, x)) return ERROR;
    if(ERROR == point_setCoordinateY(mp->input, y)) return ERROR;

    return OK;
}

Status map_setOutput (Map *mp,Point *p){
    if(!p || !mp){
        return ERROR;
    }
     int x=0, y=0;

    x = point_getCoordinateX(p);
    y = point_getCoordinateY(p);
    if(ERROR == point_setCoordinateX(mp->output, x)) return ERROR;
    if(ERROR == point_setCoordinateY(mp->output, y)) return ERROR;

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
    
    
    for(j=0; j< max_row; j++){
        for(i=0; i< max_col; i++){   

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

Map * map_readFromFile (FILE *pf){
    Map *mp=NULL;
    Point *pto=NULL;
    int i,j;
    char *aux=NULL, *aux2 =NULL;
    int ncols=0, nrows=0;

    pto = point_new(0,0,'\0');
    if(!pto){
        free(aux);
        return NULL;
    }

    aux2 = (char*) malloc (3 * sizeof(char));
    if (!aux2){
        return NULL;
    }

    if(2 != fscanf(pf, "%d %d", &nrows, &ncols)){
        free(aux2);
        point_free(pto);
        
        return NULL;
    }

    aux = (char*) malloc ((ncols+2) * sizeof(char));
    if(!aux) {
        free(aux2);
        point_free(pto);
        return NULL;
    }

    mp = map_new(nrows,ncols);
    if (!mp){
        free(aux2);
        free(aux);
        point_free(pto);
        return NULL; 
    }
    fgets(aux2, 2,pf);
    for (j = 0; j < nrows; j++)
    {
        fgets(aux, ncols+2 ,pf);
        point_setCoordinateY(pto,j);

        for(i=0; i< ncols; i++){

            point_setCoordinateX(pto,i);

            switch (aux[i])
            {
            case BARRIER:
                point_setSymbol(pto, BARRIER);
                
                break;

            case INPUT:
                point_setSymbol(pto, INPUT);
                map_setInput(mp, pto);
                
                break;
            case OUTPUT:
                point_setSymbol(pto, OUTPUT);
                map_setOutput(mp, pto);
                
                break;
            case SPACE:
                point_setSymbol(pto, SPACE);
                
                break;

            default:
                point_setSymbol(pto, ERRORCHAR);
                break;
            }
            
            mp->array[j][i] = point_hardcpy(pto);

            if(!mp->array[j][i]){
                free(aux);
                free(aux2);
                point_free(pto);
                
                return NULL;
            }
        }
    }

    free(aux);
    free(aux2);
    point_free(pto);
    

    return mp;
}
