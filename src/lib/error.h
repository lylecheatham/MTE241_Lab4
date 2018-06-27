#ifndef   ERROR_H
#define   ERROR_H

#include <stdint.h>

typedef uint8_t err_t;

void error_init(void);

void display_error(err_t err);

enum ERROR {
    ERR_NONE = 0,
    ERR_SCORE_GENERIC = 8,
    ERR_SCORE_INIT_FAIL = 9,
    ERR_SCORE_OVERFLOW = 10
};

#endif /* ERROR_H */
