#include <stdlib.h>
#include <stdio.h>
#include "bstree.h"


#define MAX_BUFFER 64 // Maximum file line size

/* START [_BSTNode] */
typedef struct _BSTNode {
    void * info;
    struct _BSTNode * left;
    struct _BSTNode * right;
    struct _BSTNode * parent;
} BSTNode;
/* END [_BSTNode] */

/* START [_BSTree] */
struct _BSTree {
    BSTNode * root;
    P_tree_ele_print print_ele;
    P_tree_ele_cmp cmp_ele;
};
/* END [_BSTree] */

Status _bst_replace_root(BSTNode* nd, BSTree* tree);

/*** BSTNode TAD private functions ***/
BSTNode * _bst_node_new(){
    BSTNode * pn = NULL;

    pn = malloc(sizeof(BSTNode));
    if (!pn) {
        return NULL;
    }
 
    pn->left = pn->right = NULL;
    pn->parent =NULL;
    pn->info = NULL;
    return pn;
}

void _bst_node_free (BSTNode * pn){
    if (!pn) return;
    if(pn->info)
        free(pn->info);
    free(pn);
}

void _bst_node_free_rec (BSTNode * pn){
    if (!pn) return;

    _bst_node_free_rec(pn->left);
    _bst_node_free_rec(pn->right);
    _bst_node_free(pn);

    return;
}

int _bst_depth_rec (BSTNode * pn) {
    int depthR, depthL;
    if (!pn) return 0;

    depthL = _bst_depth_rec(pn->left);
    depthR = _bst_depth_rec(pn->right);

    if (depthR > depthL) {
        return depthR + 1;
    } else {
        return depthL + 1;
    }
}

int _bst_size_rec(BSTNode * pn) {
    int count = 0;
    if (!pn) return count;

    count += _bst_size_rec(pn->left);
    count += _bst_size_rec(pn->right);

    return count + 1;
}

int _bst_preOrder_rec (BSTNode * pn, FILE * pf, P_tree_ele_print print_ele) {
    int count = 0;
    if (!pn) return count;

    count += print_ele(pf, pn->info);
    count += _bst_preOrder_rec(pn->left, pf, print_ele);
    count += _bst_preOrder_rec(pn->right, pf, print_ele);

    return count;
}

int _bst_inOrder_rec (BSTNode * pn, FILE * pf, P_tree_ele_print print_ele) {
    int count = 0;
    if (!pn) return count;

    count += _bst_inOrder_rec(pn->left, pf, print_ele);
    count += print_ele(pf, pn->info);
    count += _bst_inOrder_rec(pn->right, pf, print_ele);

    
    return count;
}

int _bst_postOrder_rec (BSTNode * pn, FILE * pf, P_tree_ele_print print_ele) {
    int count = 0;
    if (!pn) return count;

    count += _bst_postOrder_rec(pn->left, pf, print_ele);
    count += _bst_postOrder_rec(pn->right, pf, print_ele);
    count += print_ele(pf, pn->info);

    return count;
}

/*** BSTree TAD functions ***/
BSTree * tree_init(P_tree_ele_print print_ele, P_tree_ele_cmp cmp_ele){
   
    BSTree * tree = NULL;
   
    if (!print_ele || !cmp_ele) return NULL;

    tree = malloc (sizeof(BSTree));
    if (!tree) {
        return NULL;
    }

    tree->root = NULL;
    tree->print_ele = print_ele;
    tree->cmp_ele = cmp_ele;

    return tree;
}

void tree_destroy (BSTree * tree) {
    if (!tree) return;

    _bst_node_free_rec(tree->root);

    free(tree);
    return;
}

Bool tree_isEmpty( const BSTree * tree){
    if (!tree || !tree->root) return TRUE;
    return FALSE;
}

int tree_depth (const BSTree * tree){
    if (!tree) return -1;

    return _bst_depth_rec(tree->root);
}

size_t tree_size(const BSTree * tree) {
    if (!tree) return -1;

    return _bst_size_rec(tree->root);
}

int tree_preOrder (FILE *f, const BSTree * tree){
    if (!f || !tree) return -1;

    return _bst_preOrder_rec(tree->root, f, tree->print_ele) + fprintf(f, "\n");
}

int tree_inOrder (FILE *f, const BSTree * tree){
    if (!f || !tree) return -1;

    return _bst_inOrder_rec(tree->root, f, tree->print_ele) + fprintf(f, "\n");
}

int tree_postOrder (FILE *f, const BSTree * tree){
    if (!f || !tree) return -1;

    return _bst_postOrder_rec(tree->root, f, tree->print_ele) + fprintf(f, "\n");
}


/**** TODO: find_min, find_max, insert, contains, remove ****/
BSTNode * tree_find_min_rec(BSTNode * nd){
    
    if(nd->left==NULL) return nd;

    nd = tree_find_min_rec(nd->left);

    return nd;
}

void * tree_find_min(BSTree * tree){

    BSTNode *nd=NULL;

    if(!tree) return NULL;

    nd = tree->root;

    nd = tree_find_min_rec(nd);

    if(!nd) return NULL;

    return nd->info;
}

BSTNode * tree_find_max_rec(BSTNode * nd){
    if(nd->right==NULL) return nd;

    nd = tree_find_max_rec(nd->right);

    return nd;
}

void * tree_find_max(BSTree * tree){
    
    BSTNode *nd=NULL;

    if(!tree) return NULL;
    nd = tree->root;

    nd = tree_find_max_rec(nd);

    if(!nd) return NULL;

    return nd->info;
}


Bool tree_contains_rec(BSTNode *n, const void *e, P_tree_ele_cmp cmp_ele){
    int cmp;
    
    if(n == NULL){
        return FALSE;
    }
    
    cmp = cmp_ele(e, n->info);
    
    if(cmp < 0){
        return tree_contains_rec(n->left, e, cmp_ele);
    }
    
    if(cmp > 0){
        return tree_contains_rec(n->right, e, cmp_ele);
    }
    
    return TRUE;
}

Bool tree_contains (BSTree * tree, const void * elem) {
    if(tree == NULL || elem == NULL){
        return ERROR;
    }
    
    return tree_contains_rec(tree->root, elem, tree->cmp_ele);
}

BSTNode *_insertRec(BSTNode *pn, const void *e, P_tree_ele_cmp cmp_ele,BSTNode* father){

    int cmp;

    if (pn == NULL) {

        pn = _bst_node_new();
        if (pn == NULL) return NULL;

        pn->info = (void *) e;
        
        pn->parent = father;
        
        return pn; 
    }
   
    cmp = cmp_ele(e, pn->info);
    
    father = pn;

    if (cmp < 0)
        pn->left = _insertRec(pn->left, e, cmp_ele,father);
    else if (cmp > 0)
        pn->right = _insertRec(pn->right, e, cmp_ele,father);

    return pn; 
}

Status tree_insert(BSTree *pa, const void *pe) {
    BSTNode *pret = NULL;
    BSTNode *father = NULL;
    if (!pa || !pe) return ERROR;

    
    father = pa->root;
    
    pret = _insertRec(pa->root, pe, pa->cmp_ele,father);

    if (pret == NULL) return ERROR;

    pa->root = pret;

    return OK;
}

BSTNode *_tree_searchRec(BSTNode *pn, const void *pe, BSTree* tree){
int cmp = 0;
if (!pn) return NULL;
cmp = tree->cmp_ele(pe, pn->info);
if (cmp == 0) return pn;
if (cmp < 0) return _tree_searchRec(pn->left, pe, tree);
return _tree_searchRec(pn->right, pe, tree);
}

void *tree_search(BSTree *pt, const void *pe) {
BSTNode *found = NULL;
if (!pt || !pe) return NULL;
found = _tree_searchRec(pt->root, pe, pt);
return (found ? found->info : NULL);
}

BSTNode *tree_search_node(BSTree *pt, const void *pe) {
BSTNode *found = NULL;
if (!pt || !pe) return NULL;
found = _tree_searchRec(pt->root, pe, pt);
return (found ? found : NULL);
}

Status tree_remove (BSTree * tree, const void * elem){
    BSTNode* nd = NULL;

    if(!tree||!elem) return ERROR;

    nd = tree_search_node(tree,elem);
    if(!nd) return OK;

    return _tree_replace_root(nd,tree);
}

Status _tree_replace_root(BSTNode* nd, BSTree* tree){
    BSTNode* father = NULL;

    if(!nd->left&&!nd->right){  /*caso 1*/
        father = nd->parent;

        if(tree->cmp_ele(nd->info,father->left->info)==TRUE){ /*es el hijo izq*/
            nd->parent->left=NULL;

        }

        if(tree->cmp_ele(nd->info,father->right->info)==TRUE){  /*es el hijo der*/
            nd->parent->right=NULL;
        }

        _tree_node_free(nd);
        return OK;
    }


        

    


return OK;
}


Status test_parent(BSTree* tree){
    BSTNode * nd, *parent;

    if(!tree) return ERROR;

    fprintf(stdout,"\npadre_test1\n");
    nd = tree->root->left;
    parent = nd->parent;
    tree->print_ele(stdout,parent->info);

    fprintf(stdout,"\npadre_test2\n");
    nd = tree->root->left->left;
    parent = nd->parent;
    tree->print_ele(stdout,parent->info);

    fprintf(stdout,"\npadre_test3\n");
    nd = tree->root->right->right->right;
    parent = nd->parent;
    tree->print_ele(stdout,parent->info);

    return OK;

}


