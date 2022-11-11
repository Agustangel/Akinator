

#define MAX_LEN 128

//=========================================================================

enum akinator_codes
{
    AKTR_SUCCESS              = 0,
    ERR_AKTR_NULL_PTR         = 1,
    ERR_AKTR_BAD_FILE         = 2,
    ERR_AKTR_OUT_MEMORY       = 3,
    ERR_AKTR_BAD_SIZE         = 4,
    ERR_AKTR_BAD_POSITION     = 5,
    ERR_AKTR_BAD_MODE         = 6
};

enum MODES
{
    AKINATOR   = 1,
    DEFINITION = 2,
    DIFFERENCE = 3,
    MODE_ERROR = 4
};

//=========================================================================

int get_mode();
int play(tree_t* tree, struct string_t* strings_tree, long number_strings);
int parse_data(struct string_t* strings_tree, long number_strings, tree_t* tree);
int akinator(tree_t* tree);
