#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include "leds.h"
#include "ir.h"

int main(void)
{
    wdt_enable(WDTO_1S);

    leds_blink();

    // Set up IR
    ir_setup();

    while(1) {
        wdt_reset();

        while (ir_is_active()) {
            _delay_us(1);
        }

        uint8_t data[4] = {1, 0, 1, 0};
        ir_tx_send(data);
        _delay_ms(10);
    }

    return 0;
}
