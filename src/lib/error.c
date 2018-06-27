#include "error.h"

#include <stdio.h>

void error_init(void){
    printf("\n");
}

err_t display_error(err_t err){
    printf("ERROR: %u\n", err);
    return err;
}
