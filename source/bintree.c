#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <logger.h>

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

node_t* tree_node_ctor(const elem_t value)
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
    int verify = tree_verify(tree);
    CHECK(verify == TREE_SUCCESS, verify);

    tree_node_dtor(tree->root);
    tree->root = NULL;
    tree->size = SIZE_MAX;

    return TREE_SUCCESS;
}

//=========================================================================

void tree_node_dtor(node_t* node)
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

int insert_root(tree_t* tree, const elem_t value)
{
    CHECK(tree !=  NULL, ERR_TREE_NULL_PTR);

    node_t *newnode = tree_node_ctor(value);
    CHECK(newnode != NULL, ERR_TREE_OUT_MEMORY);

    tree->root = newnode;
    tree->size++;

    return TREE_SUCCESS;
}

//=========================================================================

int insert_node(tree_t* tree, node_t* node, int node_codes, const elem_t value)
{
    CHECK(tree !=  NULL, ERR_TREE_NULL_PTR);
    CHECK(node !=  NULL, ERR_TREE_NULL_PTR);

    int verify = tree_verify(tree);
    CHECK(verify == TREE_SUCCESS, verify);

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
        LOG("LINE: %d. ERROR: incorrect position of node\n", __LINE__);
        return ERR_TREE_BAD_POSITION;
    }

    return TREE_SUCCESS;
}

//=========================================================================

int delete_node(node_t* node)
{
    CHECK(node !=  NULL, ERR_TREE_NULL_PTR);

    if(node->left != NULL)
    {
        delete_node(node->left);
    }  
    if(node->right != NULL)
    {
        delete_node(node->right);
    }

    free(node);
    node = NULL;

    return TREE_SUCCESS;
}

//=========================================================================

int tree_verify(tree_t* tree)
{
    CHECK(tree !=  NULL, ERR_TREE_NULL_PTR);
    bool value = 0;

    value = (tree->root == NULL);
    tree->status |= value << ERR_TREE_NULL_PTR;

    value = (tree->size <= 0);
    tree->status |= value << ERR_TREE_BAD_SIZE;

    return TREE_SUCCESS;
}

//=========================================================================

int tree_dump(tree_t* tree, int print_mode)
{
    CHECK(tree !=  NULL, ERR_TREE_NULL_PTR);
    int verify = tree_verify(tree);
    CHECK(verify == TREE_SUCCESS, verify);

    if(tree->status != 0)
    {
        int error_tmp = 0;
        for(int error_idx = 1; error_idx < ERROR_NUMBER + 1; ++error_idx)
        {
            error_tmp = tree->status;
            error_tmp &= 1 << error_idx;
    
            switch (error_tmp)
            {
            case (1 << ERR_TREE_NULL_PTR):
                TREE_ERROR(ERR_TREE_NULL_PTR);
                break;

            case (1 << ERR_TREE_BAD_FILE):
                TREE_ERROR(ERR_TREE_BAD_FILE);
                break;

            case (1 << ERR_TREE_OUT_MEMORY):
                TREE_ERROR(ERR_TREE_OUT_MEMORY);
                break;

            case (1 << ERR_TREE_BAD_SIZE):
                TREE_ERROR(ERR_TREE_BAD_SIZE);
                break;

            case (1 << ERR_TREE_BAD_POSITION):
                TREE_ERROR(ERR_TREE_BAD_POSITION);
                break;

            default:
                break;
            };
        }
    }
    printf("\n");
    printf("-----------------------------------------------------------\n");
    printf("\n");

    printf("size = %zu\n", tree->size);
    printf("-----------------------------------------------------------\n");
    print_nodes(tree->root, print_mode);

    return TREE_SUCCESS;
}

//=========================================================================

void print_nodes(node_t* node, int print_mode)
{
    if (node == NULL)
    {
        return;
    }

    if(print_mode == PREORDER)
    {
        printf("%s ", node->data);
        if(node->left != NULL)
        {
            print_nodes(node->left, PREORDER);
        }
        if(node->right != NULL)
        {
            print_nodes(node->right, PREORDER);
        }  
    }
    else if(print_mode == INORDER)
    {
        if(node->left != NULL)
        {
            print_nodes(node->left, INORDER);
        }
        printf("%s ", node->data);
        if(node->right != NULL)
        {
            print_nodes(node->right, INORDER);
        }         
    }
    else if(print_mode == POSTORDER)
    {
        if(node->left != NULL)
        {
            print_nodes(node->left, POSTORDER);
        }
        if(node->right != NULL)
        {
            print_nodes(node->right, POSTORDER);
        }
        printf("%s ", node->data);
    }
    else
    {
        LOG("LINE: %d. ERROR: incorrect print mode\n", __LINE__);
    }
}

//=========================================================================

int tree_dump_graph(tree_t* tree, char* dot_out)
{
    CHECK(tree !=  NULL, ERR_TREE_NULL_PTR);

    FILE* file_dot = fopen(dot_out, "wb");
    CHECK(file_dot !=  NULL, ERR_TREE_BAD_FILE);

    fprintf(file_dot, "digraph {\n");
    fprintf(file_dot, "\tnode[shape = \"cube\", color = \"#800000\", fontsize = 15, style = \"filled\", fillcolor = \"#88CEFA\"];\n"
                      "\tedge[color = \"#190970\", fontsize = 11];\n");

    node_dump_graph(tree->root, file_dot);
    fprintf(file_dot, "}");

    fclose(file_dot);

    system("dot -Tjpeg -ograph_phys.jpeg graph_phys.dot");
    system("convert graph_log.jpeg graph_phys.jpeg -append graph_array.jpeg");
    system("gwenview graph_array.jpeg");

    return TREE_SUCCESS;
}

//=========================================================================

int node_dump_graph(node_t* node, FILE* dot_out)
{
    CHECK(node    !=  NULL, ERR_TREE_NULL_PTR);
    CHECK(dot_out !=  NULL, ERR_TREE_BAD_FILE);

    if (node->left != NULL)
    {
        fprintf(dot_out, "\n\t\t\"%s\"[shape = \"ellipse\", color=\"#900000\", style=\"filled\", fillcolor = \"#D0FDFF\"];\n"
                          "\t\t\"%s\"->\"%s\"[label = \"YES\"];\n", node->data, node->data, (node->left)->data);

        node_dump_graph(node->left, dot_out);
    }

    if (node->right != NULL)
    {
        fprintf(dot_out,
                "\n\t\t\"%s\"[shape = \"egg\", color=\"#900000\", style=\"filled\", fillcolor = \"#D0FDFF\"];\n"
                "\t\t\"%s\"->\"%s\"[label = \"NO\"];\n", node->data, node->data, (node->right)->data);

        node_dump_graph(node->right, dot_out);
    }

    return TREE_SUCCESS;
}
