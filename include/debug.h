#pragma once

/*! enumeration colors and their corresponding ANSI values. */
#define BLACK "\033[0;30m"
#define BLUE "\033[0;34m"
#define GREEN "\033[0;32m"
#define CYAN "\033[0;36m"
#define RED "\033[0;31m"
#define PURPLE "\033[0;35m"
#define BROWN "\033[0;33m"
#define YELLOW "\e[0;33m"
#define RESET "\033[0m"


static int condition__;
static int ret_;

#define CHECK(condition, retval)                                                    \
                                                                                    \
    condition__ = condition;                                                        \
    if (!condition__)                                                               \
    {                                                                               \
        ASSERT(condition__, #condition, retval);                                    \
        return retval;                                                              \
    };                                                                              \

#ifdef DEBUG
    #define ASSERT(condition, message, retval)                                      \
                                                                                    \
    if (!condition)                                                                 \
    {                                                                               \
        fprintf(stderr, "*** ASSERTION ERROR ***\n");                               \
        fprintf(stderr, "    Failed %s\n", message);                                \
        fprintf(stderr, "    Location:\n");                                         \
        fprintf(stderr, "    File ----- %s\n", __FILE__);                           \
        fprintf(stderr, "    Function - %s\n", __func__);                           \
        fprintf(stderr, "    Line ----- %d\n", __LINE__);                           \
        exit(retval);                                                               \
    }
#else
    #define ASSERT(condition, message, retval){}
#endif


//! Macros TREE_ERROR
/*! macros to print the error. */
#define TREE_ERROR(ERROR_NAME)                                                      \
{                                                                                   \
    fprintf(stderr, RED "ERROR:" RESET "line %d. " #ERROR_NAME "\n", __LINE__);     \
};

//! Macros TREE_OK
/*! macros to describe the error. */
#define TREE_OK(tree)                                                               \
                                                                                    \
    ret_ = tree_veryfi(tree);                                                       \
                                                                                    \
    switch (ret_)                                                                   \
    {                                                                               \
    case (1 << ERR_TREE_NULL_PTR):                                                  \
        TREE_ERROR(ERR_TREE_NULL_PTR);                                              \
        break;                                                                      \
                                                                                    \
    case (1 << ERR_TREE_OUT_MEMORY):                                                \
        TREE_ERROR(ERR_TREE_OUT_MEMORY);                                            \
        break;                                                                      \
                                                                                    \
    case (1 << ERR_TREE_BAD_POSITION):                                              \
        TREE_ERROR(ERR_TREE_BAD_POSITION);                                          \
        break;                                                                      \
                                                                                    \
    case (1 << ERR_TREE_BAD_FILE):                                                  \
        TREE_ERROR(ERR_TREE_BAD_FILE);                                              \
        break;                                                                      \
                                                                                    \
    case (1 << ERR_TREE_BAD_SIZE):                                                  \
        TREE_ERROR(ERR_TREE_BAD_SIZE);                                              \
        break;                                                                      \
    };
