#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>

#include "types.h"


typedef struct _Node Node ;


Node* node_new();

Status node_free();

Status node_set_info(Node* nd, void* ele);
void* node_get_info(Node* nd);

Status node_set_next(Node* nd, Node* next);
Node* node_get_next(Node* nd);