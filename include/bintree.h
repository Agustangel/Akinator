#pragma once

#include <stdio.h>
#include <stdint.h>


#define DATA_POISON 0
#define ERROR_NUMBER 5

//=========================================================================

typedef char* elem_t;
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
    ERR_TREE_OUT_MEMORY       = 2,
    ERR_TREE_BAD_SIZE         = 3,
    ERR_TREE_BAD_POSITION     = 4,
    ERR_TREE_BAD_STRING       = 5,
    ERR_TREE_BAD_FILE         = 6
};

enum node_codes
{
    LEFT  = 0,
    RIGHT = 1
};

enum print_mode
{
    PREORDER  = 1,
    POSTORDER = 2,
    INORDER   = 3
};

//=========================================================================

int tree_ctor(tree_t* tree);
node_t* tree_node_ctor(const elem_t value);
int tree_dtor(tree_t* tree);
void tree_node_dtor(node_t* node);
int insert_node(tree_t* tree, node_t* node, int node_codes, const elem_t value);
int inser_root(tree_t* tree, node_t* node, const elem_t value);
int delete_node(node_t* node);
int tree_verify(tree_t* tree);
void print_nodes(node_t* node, int print_mode);
int tree_dump(tree_t* tree, int print_mode);
int tree_dump_graph(tree_t* tree, char* dot_out);
int node_dump_graph(node_t* node, FILE* dot_out);
