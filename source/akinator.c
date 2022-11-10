
#include <stdio.h>
#include <akinator.h>
#include <bintree.h>
#include <onegin.h>


//=========================================================================
int play(tree_t* tree, struct string_t* strings_tree, long number_strings)
{
    CHECK(tree != NULL, ERR_TREE_NULL_PTR);

    node_t* current_node = tree->root;
    for(int idx = 0; idx < number_strings; ++idx)
    {
        parse_data(strings_tree[idx], current_node); // ? node
    }

    int mode = get_mode();
    CHECK(mode != MODE_ERROR, ERR_AKTR_BAD_MODE);

    switch (mode)
    {
    case AKINATOR:
        /* code */
        break;
    
    case DEFINITION:
        /* code */
        break;

    case DIFFERENCE:
        /* code */
        break;

    default:
        break;
    }

    return TREE_SUCCESS;
}

//=========================================================================

int get_mode()
{
    printf("Enter game mode: \b");
    printf("(1) Akinator;\n");
    printf("(2) Definition;\n");
    printf("(3) Difference;\n");

    int resp = EOF;
    while ((resp = getchar()) != EOF)
    {
        switch (resp)
        {
            case '1':
                return AKINATOR;
            case '2':
                return DEFINITION;
            case '3':
                return DIFFERENCE;

            default:
                printf("Undefined mode. Input again\n");
                return MODE_ERROR;
        }
    }

    return MODE_ERROR;
}

//=========================================================================

int parse_data(struct string_t string_tree, node_t* node)
{
    char* current_position = string_tree->begin_string;
    CHECK(current_position != NULL, ERR_TREE_NULL_PTR);

    if(*current_position == '{')
    {
        ++current_position;
        if(*current_position == 'l')
        {
            node = node->left;
            // CHECK node
        }
        else if(*current_position == 'r')
        {
            node = node->right;
            // CHECK node            
        }
    }

    return AKTR_SUCCESS;
}
