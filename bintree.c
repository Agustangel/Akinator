#include <stdio.h>
#include <stdlib.h>

#include "bintree.h"
#include "debug.h"


//=========================================================================
int tree_ctor(tree_t* tree)
{
    CHECK(tree !=  NULL, ERR_TREE_NULL_PTR);

    tree->root = NULL;
    tree->size = 0;

    return TREE_SUCCESS;
}

//=========================================================================

static node_t* tree_node_ctor(const elem_t value)
{
    node_t* node = (node_t*) calloc(1, sizeof(node_t));
    CHECK(node !=  NULL, NULL);

    node->data = value;
    node->left = NULL;
    node->right = NULL;
    
    return node;
}

//=========================================================================
