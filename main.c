#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Light_WS2812/light_ws2812.h"

struct cRGB led[2];

int main(void)
{
    DDRB |= (1 << DDB0);

    while(1) {
        int max = 10;
        int delay = 10;

        int max_max = 255;
        int max_2 = abs(max / 2);
        int adj_delay = abs(max_max / max * delay);
        for (int i = 0; i < max; i++) {
            led[0].r = i; led[0].g = max - i; led[0].b = i < max_2 ? max_2 + i : i - max_2;
            led[1].g = i; led[1].b = max - i; led[1].r = i < max_2 ? max_2 + i : i - max_2;
            ws2812_setleds(led, 2);
            _delay_ms(adj_delay);
        }
    }

    return 0;
}
