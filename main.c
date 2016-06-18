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

    ir_setup();
    ir_tx_init();

    while(1) {
        wdt_reset();

        //leds_run(10, 10);

        while (ir_tx_active()) {
            _delay_us(1);
        }

        uint8_t data[4] = {1, 0, 1, 0};
        ir_tx_send(data);
        _delay_us(100);
    }

    return 0;
}

ISR(PCINT2_vect)
{
    cli();

    //leds_blink();

    sei();
}
