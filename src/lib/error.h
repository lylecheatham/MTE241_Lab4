#include <stdint.h>

typedef uint8_t err_t;

void display_error();

enum ERROR{
    ERR_NONE = 0,
    ERR_SCORE_GENERIC = 8,
    ERR_SCORE_INIT_FAIL = 9,
    ERR_SCORE_OVERFLOW = 10
}
