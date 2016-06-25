#include "Light_WS2812/light_ws2812.h"

#ifndef __leds_h_included__
#define __leds_h_included__

/**
 * Set a led
 *  id: Led ID to set
 *  rgb: Color to set LED to
 */
void leds_set(int id, struct cRGB rgb);

/**
 * Cycle all leds through the full color spectrum
 *
 *  brightness: Led brightness (1-255)
 *  delay: Delay beteween updates
 */
void leds_run(int brightness, int delay);

/**
 * Disable all leds
 */
void leds_off();

/**
 * Blink all leds white
 */
void leds_on();

/**
 * Blink all leds
 */
void leds_blink(struct cRGB color);

#endif
