#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Light_WS2812/light_ws2812.h"

uint8_t leds_count = 5;
struct cRGB leds[5];

void leds_set(int id, struct cRGB rgb)
{
    leds[id] = rgb;
    ws2812_setleds(leds, leds_count);
}

void leds_run(int brightness, int delay)
{
    int brightness_max = 255;
    int brightness_2 = abs(brightness / 2);
    int adj_delay = abs(brightness_max / brightness * delay);

    int j;
    struct cRGB color, color2, color3;
    for (int i = 0; i < brightness; i++) {
        color.r = i;
        color.g = brightness - i;
        color.b = i < brightness_2 ? brightness_2 + i : i - brightness_2;

        color2.r = color.b;
        color2.g = color.g;
        color2.b = color.r;

        color3.r = color.g;
        color3.g = color.r;
        color3.b = color.b;

        leds_set(0, color);
        leds_set(1, color2);
        leds_set(2, color3);
        leds_set(3, color);
        leds_set(4, color2);

        j = adj_delay;
        while (j--) {
            _delay_ms(1);
        }
    }
}

void leds_off()
{
    struct cRGB color = {0, 0, 0};
    for (int i = 0; i < leds_count; i++) {
        leds_set(i, color);
    }

    ws2812_setleds(leds, leds_count);
}

void leds_on()
{
    struct cRGB color = {20, 20, 20};
    for (int i = 0; i < leds_count; i++) {
        leds_set(i, color);
    }

    _delay_ms(500);

    leds_off();
}

void leds_blink(struct cRGB color)
{
    for (int i = 0; i < leds_count; i++) {
        leds_set(i, color);
    }

    _delay_ms(500);

    leds_off();
}
