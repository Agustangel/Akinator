#pragma once


//=========================================================================

typedef int elem_t;

typedef struct node_t
{
    elem_t data;
    node_t* left;
    node_t* right;

} node_t;

typedef struct tree_t
{
    node_t* root;
    size_t size;

} tree_t;

//=========================================================================

enum tree_codes
{
    TREE_SUCCESS              = 0,
    ERR_TREE_NULL_PTR         = 1,
    ERR_TREE_BAD_PTR          = 2,
    ERR_TREE_OUT_MEMORY       = 3,
    ERR_TREE_BAD_SIZE         = 4,
    ERR_TREE_INC_TREE         = 8
};

//=========================================================================

int tree_ctor(node_t* tree);
