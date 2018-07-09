#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>

#include "error.h"

err_t button_task_init(void);

uint32_t button_press_get(void);

#endif /* BUTTON_H */
