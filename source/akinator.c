
#include <stdio.h>
#include <onegin.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "akinator.h"
#include "bintree.h"
#include "debug.h"

//=========================================================================
int play(tree_t* tree, struct string_t* strings_tree, long number_strings)
{
    CHECK(tree         != NULL, ERR_TREE_NULL_PTR);
    CHECK(strings_tree != NULL, ERR_TREE_NULL_PTR);
   
    int status = 0;
    status = parse_data(strings_tree, number_strings, tree, tree->root);
    CHECK(status == AKTR_SUCCESS, status);

    int mode = get_mode();
    CHECK(mode != MODE_ERROR, ERR_AKTR_BAD_MODE);
    
    switch (mode)
    {
    case DIVINATION:
        status = akinator(tree);
        CHECK(status == AKTR_SUCCESS, status);
        break;
    
    case DEFINITION:
        status = definition(tree);
        CHECK(status == AKTR_SUCCESS, status);
        break;

    case VISUALIZATION:
        status = tree_dump_graph(tree, "graph_phys.dot");
        CHECK(status == TREE_SUCCESS, status);
        break;

    default:
        break;
    }

    return AKTR_SUCCESS;
}

//=========================================================================

int get_mode()
{
    printf("Enter game mode:\n");
    printf("(1) Divination;\n");
    printf("(2) Definition;\n");
    printf("(3) Visualization;\n");

    int resp = EOF;
    while ((resp = getchar()) != EOF)
    {
        switch (resp)
        {
            case '1':
                return DIVINATION;
            case '2':
                return DEFINITION;
            case '3':
                return VISUALIZATION;

            default:
                printf("Undefined mode. Input again\n");
                return MODE_ERROR;
        }
    }

    return MODE_ERROR;
}

//=========================================================================

int parse_data(struct string_t* strings_tree, long number_strings, tree_t* tree, node_t* node)
{
    CHECK(tree         != NULL, ERR_TREE_NULL_PTR);
    CHECK(strings_tree != NULL, ERR_TREE_NULL_PTR);
    CHECK(number_strings > 0, ERR_AKTR_BAD_SIZE);

    static int idx = 0;
    if(tree->root == NULL)
    {
        insert_root(tree, strings_tree[idx].begin_string);
        ++idx;
        node = tree->root;
        parse_data(strings_tree, number_strings, tree, node);
    }
    
    CHECK((idx + 1) != number_strings, AKTR_SUCCESS);
    if(strcasecmp(strings_tree[idx].begin_string, "{l") == 0)
    {
        insert_node(tree, node, LEFT, strings_tree[idx + 1].begin_string);
        idx += 2;
        parse_data(strings_tree, number_strings, tree, node->left);
    }
    
    CHECK((idx + 1) != number_strings, AKTR_SUCCESS);
    if(strcasecmp(strings_tree[idx].begin_string, "{r") == 0)
    {
        insert_node(tree, node, RIGHT, strings_tree[idx + 1].begin_string);
        idx += 2;
        parse_data(strings_tree, number_strings, tree, node->right);
    }
    
    CHECK((idx + 1) != number_strings, AKTR_SUCCESS);
    if(strcasecmp(strings_tree[idx].begin_string, "}") == 0)
    {
        idx++;
    }

    return AKTR_SUCCESS;
}

//=========================================================================

int akinator(tree_t* tree)
{
    CHECK(tree != NULL, ERR_TREE_NULL_PTR);

    node_t* node = tree->root;
    char answ = '\0';

    while((node->left != NULL) && (node->right != NULL))
    {
        printf("It is %s\n", node->data);
        do
        {
            answ = getchar();
        }
        while((answ != 'y') && (answ != 'n'));

        if(answ == 'y')
        {
            node = node->left;
        }
        else if(answ == 'n')
        {
            node = node->right;
        }
    }

    printf("It is %s\n", node->data);
    do
    {
        answ = getchar();
    }
    while((answ != 'y') && (answ != 'n'));

    if(answ == 'y')
    {
        printf("Guessed right!\n");
    }
    else if(answ == 'n')
    {
        clear_buffer();
        int status = unknowen(tree, node);
        CHECK(status == AKTR_SUCCESS, status);
    }

    FILE* savefile = fopen("in_data.txt", "w");
    CHECK(savefile != NULL, ERR_AKTR_BAD_FILE);
    savedata(savefile, tree->root, tree->root);
    fclose(savefile);

    return AKTR_SUCCESS;
}

//=========================================================================

int unknowen(tree_t* tree, node_t* node)
{
    CHECK(tree != NULL, ERR_TREE_NULL_PTR);
    CHECK(node != NULL, ERR_TREE_NULL_PTR);

    printf("What did you mean?\n");
    char* newdata = get_answer();
    CHECK(newdata != NULL, ERR_AKTR_OUT_MEMORY);

    char* olddata = node->data;

    printf("What is the difference between %s and %s in all?\n", newdata, node->data);
    node->data = get_answer();
    CHECK(node->data != NULL, ERR_AKTR_OUT_MEMORY);

    insert_node(tree, node, LEFT, newdata);
    insert_node(tree, node, RIGHT, olddata);

    return AKTR_SUCCESS; 
}

//=========================================================================

void clear_buffer()
{
    int ch = 0;
    while((ch = getchar()) != '\n' && ch != EOF);
}

//=========================================================================

char* get_answer()
{
    char* data = NULL;
    size_t len = MAX_LEN;
    CHECK(getline(&data, &len, stdin) != -1, NULL);

    char* last_symbol = strchr(data, '\n');
    if(last_symbol != NULL)
    {
        last_symbol = '\0';
    }

    return data;
}

//=========================================================================

int savedata(FILE* file, node_t* node, node_t* root)
{
    CHECK(file != NULL, ERR_TREE_BAD_FILE);
    CHECK(node != NULL, ERR_TREE_NULL_PTR);
    CHECK(root != NULL, ERR_TREE_NULL_PTR);

    fprintf(file, "%s\n", node->data);

    if(node->left != NULL)
    {
        fprintf(file, "{l\n");
        savedata(file, node->left, root);
    }
    if(node->right != NULL)
    {
        fprintf(file, "{r\n");
        savedata(file, node->right, root);
    }

    if(node != root)
    {
        fprintf(file, "}\n");
    }

    return AKTR_SUCCESS;
}

//=========================================================================

int definition(tree_t* tree)
{
    CHECK(tree != NULL, ERR_TREE_NULL_PTR);

    clear_buffer();

    printf("Input something to definition: \n");
    char* lookdata = get_answer();
    CHECK(lookdata != NULL, ERR_AKTR_OUT_MEMORY);

    if(definition_rec(tree->root, lookdata))
    {
        printf("I did it!\n");
    }
    else
    {
        printf("Object not found\n");
    }

    free(lookdata);

    return AKTR_SUCCESS;
}

//=========================================================================

bool definition_rec(node_t* node, char* object)
{
    CHECK(node   != NULL, false);
    CHECK(object != NULL, false);

    if((node->left != NULL) && (node->right != NULL))
    {
        if(definition_rec(node->left, object))
        {
            printf(", %s", node->data);
            return true;
        }
        else if(definition_rec(node->right, object))
        {
            printf(", not %s", node->data);
            return true; 
        }
        else
        {
            return false;
        }
    }
    else
    {
        CHECK(node->data != NULL, false);
        if(strcasecmp(node->data, object) == 0)
        {
            printf("%s is defined", node->data);
            return true;
        }
    }

    return false;
}

//=========================================================================
