#include <RTL.h>
#include <stdint.h>
#include <stdio.h>
#include "GLCD.h"
#include "pot.h"
#include "led.h"
#include "util.h"
#include "button.h"
#include "joystick.h"

__task void button_task() {
    init_joystick();
    GLCD_Init();
    GLCD_Clear(Blue);
    GLCD_SetBackColor(Blue);
    GLCD_SetTextColor(White);

    while (1) {
        uint32_t dir = 0;
        GLCD_Clear(Blue);

        dir = get_joystick_dir();

        switch (dir) {
            case DIR_NO_INPUT: {
                GLCD_DisplayString(5, 4, 1, "NO DIR");
                break;
            }

            case DIR_UP: {
                GLCD_DisplayString(5, 4, 1, "UP");
                break;
            }

            case DIR_RIGHT: {
                GLCD_DisplayString(5, 4, 1, "RIGHT");
                break;
            }

            case DIR_DOWN: {
                GLCD_DisplayString(5, 4, 1, "DOWN");
                break;
            }

            case DIR_LEFT: {
                GLCD_DisplayString(5, 4, 1, "LEFT");
                break;
            }
        }
        if (get_joystick_pressed()) {
            GLCD_DisplayString(6, 4, 1, "PRESSED");
        } else {
            GLCD_DisplayString(6, 4, 1, "NOT PRESSED");
        }
        os_tsk_pass();
    }
}

__task void game_loop_task() {
    uint8_t LEDState = 0;
    init_LEDs();

    while (1) {
        // Check to see if the button has been pressed, pass task if not pressed
        while (get_button_press() == 0) {
            os_tsk_pass();
        }
        // Button has now been pressed

        // toggle the LED
        LEDState ^= 1;

        // Output the value to the LED
        display_number(LEDState);

        // Pass the task while the button stays pressed
        while (get_button_press() == 1) {
            os_tsk_pass();
        }
    }
}

__task void start_tasks() {
    // Create all other tasks


    // Delete task because no longer needed
    os_tsk_delete_self();

    // Belt and suspenders
    while (1) {
        os_tsk_pass();
    }
}

int main(void) {
    uint32_t exercise = 6;
    uint32_t temp = 0;

    if (exercise == 1) {
        init_LEDs();
        display_number(123);
    } else if (exercise == 2) {
        init_LEDs();
        init_joystick();

        while (1) {
            temp = get_joystick_dir();

            display_number(temp);

            if (temp != 0) {
                switch (temp) {
                    case 1: {
                        printf("UP\r\n");
                        break;
                    }

                    case 2: {
                        printf("RIGHT\r\n");
                        break;
                    }

                    case 3: {
                        printf("DOWN\r\n");
                        break;
                    }

                    case 4: {
                        printf("LEFT\r\n");
                        break;
                    }

                    case 5: {
                        printf("PRESSED\r\n");
                        break;
                    }
                }
            }
        }
    } else if (exercise == 3) {
        init_LEDs();
        while (1) {
            display_number(get_button_press());
        }
    } else if (exercise == 4) {
        init_LEDs();
        init_potentiometer();

        while (1) {
            uint32_t value = get_potentiometer_position();
            value = value >> 4;
            display_number(value);
        }

    } else if (exercise == 5) {
        GLCD_Init();
        GLCD_Clear(Blue);
        GLCD_SetBackColor(Blue);
        GLCD_SetTextColor(White);
        while (1) {
            GLCD_DisplayString(5, 4, 1, "Hello World");
        }

    } else if (exercise == 6) {
        printf("asdf");  // Initialize the UART before RTOS starts

        os_sys_init(start_tasks);
    }

    while (1)
        ;
}
