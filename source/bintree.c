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

int tree_dtor(tree_t* tree)
{
    CHECK(tree !=  NULL, ERR_TREE_NULL_PTR);

    tree_node_dtor(tree->root);
    tree->root = NULL;
    tree->size = SIZE_MAX;

    return TREE_SUCCESS;
}

//=========================================================================

static void tree_node_dtor(node_t* node)
{
    if (node == NULL)
    {
        return;
    }

    tree_node_dtor(node->right);
    tree_node_dtor(node->left);
    free(node);
}

//=========================================================================

int insert_node(tree_t* tree, node_t* node, enum node_codes, const elem_t value)
{
    CHECK(tree !=  NULL, ERR_TREE_NULL_PTR);
    CHECK(node !=  NULL, ERR_TREE_NULL_PTR);

    node_t *newnode = tree_node_ctor(value);
    CHECK(newnode != NULL, ERR_TREE_OUT_MEMORY);

    if(node_codes == LEFT)
    {
        node->left = newnode;
        tree->size++;
    }
    else if(node_codes == RIGHT)
    {
        node->right = newnode;
        tree->size++;
    }
    else
    {
        return ERR_TREE_BAD_POSITION;
    }

    return TREE_SUCCESS;
}

//=========================================================================
