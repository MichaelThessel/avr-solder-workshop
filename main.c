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

    while(1) {
        wdt_reset();

        //leds_run(10, 10);

        IR_TX_ON();
        _delay_us(10);
        IR_TX_OFF();
        _delay_ms(500);
    }

    return 0;
}

ISR(PCINT2_vect)
{
    cli();

    //leds_blink();

    sei();
}
