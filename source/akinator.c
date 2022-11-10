
#include <stdio.h>
#include <akinator.h>
#include <bintree.h>
#include <onegin.h>


//=========================================================================
int play(tree_t* tree)
{
    CHECK(tree != NULL, ERR_TREE_NULL_PTR);

    FILE* file = open_file("in_data.txt");
    CHECK(file != NULL, ERR_TREE_BAD_FILE);

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
