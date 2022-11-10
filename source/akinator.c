
#include <stdio.h>
#include <akinator.h>
#include <bintree.h>
#include <onegin.h>


//=========================================================================
int play(tree_t* tree)
{
    CHECK(tree != NULL, ERR_TREE_NULL_PTR);

    FILE* text = open_file("in_data.txt");
    CHECK(text != NULL, ERR_AKTR_BAD_FILE);

    struct string_t* strings_tree = NULL;
    strings_tree = get_strings_tree(text);
    CHECK(strings_tree != NULL, ERR_TREE_NULL_PTR);

    fclose(text);

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
// from onegin
void get_strings_tree(FILE* text, struct string_t* strings)
{
    long count = count_symbols(text);
    HANDLE_ERROR(count, ERR_TXT_BAD_PTR, "ERROR: pointer outside file.\n");

    char* buffer = (char*) calloc(count, sizeof(char));
    int ret = fill_buffer(text, buffer, sizeof(char), count);
    HANDLE_ERROR(ret, ERR_TXT_BAD_READ, "ERROR: file read error.\n");

    long number_strings = count_strings(buffer, count);
    strings = get_strings(buffer, count, number_strings);

}

//=========================================================================

int parse_data(struct string_t* strings_tree, node_t* node)
{


    return AKTR_SUCCESS;
}
