#include <util/delay.h>
#include "leds.h"
#include "ir.h"

void game_setup()
{
    // Set up IR
    ir_setup();
}

void game_loop()
{
    while (ir_is_active()) {
        _delay_us(1);
    }

    uint8_t data[4] = {1, 1, 1, 0};
    ir_tx_send(data);
    _delay_ms(10);
}

void ir_rx_success(uint8_t data[4])
{
    if (data[0] == 1 && data[1] == 1 && data[2] == 1 && data[3] == 0) {
        struct cRGB color = {20, 0, 0}; // Green
        leds_set(1, color);
        _delay_ms(300);
        leds_off();
    }
}
