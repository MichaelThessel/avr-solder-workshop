#ifndef __leds_h_included__
#define __leds_h_included__
/**
 * Cycle all leds through the full color spectrum
 *
 * @param brightness Led brightness (1-255)
 * @param delay Delay beteween updates
 */
void leds_run(int, int);

#endif
