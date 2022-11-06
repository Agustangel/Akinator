#include <stdio.h>

#include "bintree.h"
#include "debug.h"


int main()
{
    node_t tree;
    tree_ctor(&tree);
    tree_dtor(&tree);

    return 0;
}
