#include <stdint.h>

// RESETS
#define RESETS_RESET        (*(volatile uint32_t *)0x4000C000)
#define RESETS_RESET_DONE   (*(volatile uint32_t *)0x4000C008)

// IO BANK0: GPIO 04
#define IO_BANK0_GPIO04_CTRL (*(volatile uint32_t *)0x40014024)

// SIO
#define SIO_GPIO_OE_SET     (*(volatile uint32_t *)0xD0000024)
#define SIO_GPIO_OUT_XOR    (*(volatile uint32_t *)0xD000001C)

// Main entry point
int main(void)
{
    // Bring IO_BANK0 out of reset state
    RESETS_RESET &= ~(1 << 5);
    while (!(RESETS_RESET_DONE & (1 << 5)));

    // Set GPIO 04 function to SIO
    IO_BANK0_GPIO04_CTRL = 5;

    // Set output enable for GPIO 04 in SIO
    SIO_GPIO_OE_SET |= 1 << 4;

    for ( ;; ) {
        // Wait for some time
        for (uint32_t i = 0; i < 100000; ++i);

        // Flip output for GPIO 04
        SIO_GPIO_OUT_XOR |= 1 << 4;
    }
}
