#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "leds.h"
#include "ir.h"

void leds_blink()
{
    struct cRGB color = {20, 20, 20};
    leds_set(0, color);
    leds_set(1, color);

    _delay_ms(500);

    leds_off();
}

int main(void)
{
    leds_blink();

    ir_setup();

    while(1) {
        ;
        //leds_run(10, 10);

        IR_TX_ON();
        _delay_us(10);
        IR_TX_OFF();
        _delay_ms(1000);
    }

    return 0;
}

ISR(PCINT2_vect)
{
    cli();

    leds_blink();

    sei();
}
