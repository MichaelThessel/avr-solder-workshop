#include <avr/io.h>
#include <util/delay.h>
#include "leds.h"
#include "ir.h"

// IR configuration


int main(void)
{
    ir_setup();

    while(1) {
        //leds_run(10, 10);

        IR_LED_ON();
        _delay_ms(100);
        IR_LED_OFF();
        _delay_ms(100);
    }

    return 0;
}
