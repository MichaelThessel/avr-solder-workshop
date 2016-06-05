#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Light_WS2812/light_ws2812.h"

struct cRGB led[2];

void leds_run(int brightness, int delay)
{
    int brightness_max = 255;
    int brightness_2 = abs(brightness / 2);
    int adj_delay = abs(brightness_max / brightness * delay);

    int i, j;
    for (i = 0; i < brightness; i++) {
        led[0].r = i;
        led[0].g = brightness - i;
        led[0].b = i < brightness_2 ? brightness_2 + i : i - brightness_2;

        led[1].g = i;
        led[1].b = brightness - i;
        led[1].r = i < brightness_2 ? brightness_2 + i : i - brightness_2;

        ws2812_setleds(led, 2);

        j = adj_delay;
        while (j--) {
            _delay_ms(1);
        }
    }
}
