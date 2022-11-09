#include <stdio.h>
#include <logger.h>
#include <onegin.h>

#include "bintree.h"
#include "debug.h"


int main()
{
    logger_init(1, "akinator.log");
    logger_set_level(INFO);

    tree_t tree;
    tree_ctor(&tree);
    tree_dtor(&tree);

    logger_finalize(file);
    
    return 0;
}
