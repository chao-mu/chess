#include <assert.h>
#include <stdio.h>

#define assert_true(x) \
    assert(x);         \
    fprintf(stderr, ".");

#define test_start(x)   \
    fprintf(stderr, x); \
    fprintf(stderr, " ");

#define test_end() fprintf(stderr, " ok\n");
