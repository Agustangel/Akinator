#pragma once

#include <stdio.h>
#include <stdint.h>


#define DATA_POISON = 0;

//=========================================================================

typedef int elem_t;
typedef uint_fast16_t treeStatus_t;

typedef struct node_t node_t;
struct node_t
{
    elem_t data;
    node_t* left;
    node_t* right;

};

typedef struct tree_t
{
    node_t* root;
    size_t size;

    treeStatus_t status;

} tree_t;

//=========================================================================

enum tree_codes
{
    TREE_SUCCESS              = 0,
    ERR_TREE_NULL_PTR         = 1,
    ERR_TREE_BAD_PTR          = 2,
    ERR_TREE_OUT_MEMORY       = 3,
    ERR_TREE_BAD_SIZE         = 4,
    ERR_TREE_BAD_POSITION     = 5
};

enum node_codes
{
    LEFT  = 0,
    RIGHT = 1
};

//=========================================================================

int tree_ctor(tree_t* tree);
static node_t* tree_node_ctor(const elem_t value);
int tree_dtor(tree_t* tree);
static void tree_node_dtor(node_t* node);
int insert_node(tree_t* tree, node_t* node, int node_codes, const elem_t value);
int tree_verify(tree_t* tree);
