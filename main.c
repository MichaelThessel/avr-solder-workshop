#include <avr/io.h>
#include <util/delay.h>
#include "leds.h"
#include "ir.h"

int main(void)
{
    ir_setup();

    while(1) {
        //leds_run(10, 10);

        IR_TX_ON();
        _delay_us(1);
        IR_TX_OFF();
        _delay_us(9);
    }

    return 0;
}
