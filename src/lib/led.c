#include "led.h"
#include <lpc17xx.h>
#include "util.h"

void init_LEDs(void) {
    LPC_GPIO2->FIODIR |= 0x0000007C;
    LPC_GPIO1->FIODIR |= 0xB0000000;
    LPC_GPIO1->FIOCLR = 0x0000007C;
    LPC_GPIO2->FIOCLR = 0xB0000000;
}

// Displays a number using the LEDs on the bottom of the board
//
// Parameters:
//   uint8_t num: The number to display
//
// Returns:
//   void
void display_number(uint8_t num) {
    // Initialize masks to 0
    uint32_t GPIO1_mask = 0x00000000;
    uint32_t GPIO2_mask = 0x00000000;

    // Set all of the LED bits to 0 to turn off the LEDs
    LPC_GPIO1->FIOCLR |= 0xB0000000;
    LPC_GPIO2->FIOCLR |= 0x0000007C;

    // Set the GPIO1 & GPIO2 masks
    GPIO2_mask |= get_bit(num, 0) << 6;
    GPIO2_mask |= get_bit(num, 1) << 5;
    GPIO2_mask |= get_bit(num, 2) << 4;
    GPIO2_mask |= get_bit(num, 3) << 3;
    GPIO2_mask |= get_bit(num, 4) << 2;

    GPIO1_mask |= get_bit(num, 5) << 31;
    GPIO1_mask |= get_bit(num, 6) << 29;
    GPIO1_mask |= get_bit(num, 7) << 28;

    // Apply masks to GPIO1 and GPIO2
    LPC_GPIO2->FIOSET |= GPIO2_mask;
    LPC_GPIO1->FIOSET |= GPIO1_mask;
}
