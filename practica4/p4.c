#include <stdlib.h>
#include <stdio.h>
#include "bstree.h"
#include "point.h"


BSTree * tree_read_points_from_file(FILE * pf);


int main (int argc, char *argv[]){

    BSTree* tree;
    FILE *pf;

    if(argc != 2) return -1;

    pf = fopen(argv[1], "r");
    if(!pf) return -1;

    tree = tree_read_points_from_file(pf);
    if(!tree){
        tree_destroy(tree);
        fclose(pf);
        return -1;
    }

    fprintf(stdout,"preOrder\n");
    tree_preOrder(stdout,tree);

    fprintf(stdout,"inOrder\n");
    tree_inOrder(stdout,tree);

    fprintf(stdout,"find_min\n");
    point_print(stdout,tree_find_min(tree));

    fprintf(stdout,"\n");

    fprintf(stdout,"find_max\n");
    point_print(stdout,tree_find_max(tree));

    fprintf(stdout,"\n");

    if(TRUE == tree_contains(tree, tree_find_min(tree))) fprintf(stdout, "the min is contained");
    else fprintf(stdout, "the min is contained");

    fprintf(stdout,"\n");

    if(TRUE == tree_contains(tree, tree_find_max(tree))) fprintf(stdout, "the max is contained");
    else fprintf(stdout, "the max is contained");

    fprintf(stdout,"\n");

    fprintf(stdout,"mi test");

    test_parent(tree);

    tree_destroy(tree);
    fclose(pf);
    return 0;

}


BSTree * tree_read_points_from_file(FILE * pf){
    BSTree * t;
    int nnodes=0, i;
    Status st = OK;
    int x, y;
    char symbol;
    Point * p;

    if (!pf){
        return NULL;
    }

    /* Read number of nodes */
    if (fscanf(pf, "%d\n", &nnodes) != 1){
        return NULL;
    }
    
    /* Create tree */
    t = tree_init(point_print, point_cmpEuDistance);
    if(!t){
        return NULL;
    }

    /* Read nodes */
    for (i=0; i<nnodes && st==OK ;i++){
        if(fscanf(pf, "%d %d %c", &x, &y, &symbol)!=3){
            return NULL;
        }
        p=point_new(x, y, symbol);
        if(!p){
            tree_destroy(t);
            return NULL;
        }

        st=tree_insert(t, p); 
        if(st==ERROR){
            tree_destroy(t);
            point_free(p);
            return NULL;      
        }

    }


    return t;






}
