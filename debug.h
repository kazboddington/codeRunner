#ifndef DEBUG_H
#define DEBUG_H
#include <stdio.h>
#define debug_print(FMT, ARGS...) do { \
        fprintf(stderr, "%s:%d " FMT "\n", __FUNCTION__, __LINE__, ## ARGS); \
        } while (0)

#endif /* DEBUG_H */

