#include <util/delay.h>
#include "leds.h"
#include "game.h"

int main(void)
{
    // Boot
    struct cRGB color = {0, 0, 10};
    leds_set(1, color);
    _delay_ms(1000);
    leds_off();

    // Set up game
    game_setup();

    while(1) {
        // Game loop
        game_loop();
    }

    return 0;
}
