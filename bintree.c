#include <stdio.h>

#include "bintree.h"
#include "debug.h"


int tree_ctor(node_t* tree)
{
    CHECK(tree !=  NULL, ERR_TREE_NULL_PTR);

    tree->data = 0;
    tree->left = NULL;
    tree->right = NULL;
    
    return TREE_SUCCESS;
}
