#include <stdio.h>
#include <logger.h>
#include <onegin.h>

#include "bintree.h"
#include "akinator.h"
#include "debug.h"


int main()
{
    logger_init(1, "akinator.log");
    logger_set_level(INFO);

    tree_t tree;
    tree_ctor(&tree);

    FILE* text = open_file("../in_data.txt");
    CHECK(text != NULL, ERR_AKTR_BAD_FILE);

    long count = count_symbols(text);
    HANDLE_ERROR(count, ERR_TXT_BAD_PTR, "ERROR: pointer outside file.\n");

    char* buffer = (char*) calloc(count, sizeof(char));
    int ret = fill_buffer(text, buffer, sizeof(char), count);
    HANDLE_ERROR(ret, ERR_TXT_BAD_READ, "ERROR: file read error.\n");

    fclose(text);

    long number_strings = count_strings(buffer, count);
    struct string_t* strings_tree = get_strings(buffer, count, number_strings);

    int ret = 0;
    do
    {
        ret = play(&tree, strings_tree, number_strings);

    } while (ret == ERR_AKTR_BAD_MODE);

    tree_dtor(&tree);
    logger_finalize(file);
    
    return 0;
}
