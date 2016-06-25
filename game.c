#include <util/delay.h>
#include "leds.h"

uint8_t game_debounce_active = 0;

void game_setup()
{
    DDRC &= ~(1 << DDC0); // Configure PC0 as input
    DDRC &= ~(1 << DDC1); // Configure PC1 as input

    PORTC |= (1 << PORTC0) | (1 << PORTC1); // Pull PC0 & PC1 high

    PCICR |= (1 << PCIE1); // Enable pin change interrupts for [14:8]
    PCMSK1 |= (1 << PCINT8) | (1 << PCINT9); // Enable pin change interrupt for PCINT8 & 9
    EICRA |= (1 << ISC11); // Trigger pin change interrupt on falling edge

    sei(); // Global interrupt enable
}

void game_loop()
{
    leds_run(10, 10);
}

void game_button1_press()
{
    struct cRGB color = {0, 20, 0};
    leds_blink(color);
}

void game_button2_press()
{
    struct cRGB color = {20, 0, 0};
    leds_blink(color);
}

// Enable debounce
void game_debounce()
{
    game_debounce_active = 1;
    TCCR0B |= (1 << CS00) | (1 << CS01); // prescaler 1024
    TIMSK0 |= (1 << OCIE0A); // Enable timer compare match interrupt
}

// Handle button pushes
ISR(PCINT1_vect)
{
    if (game_debounce_active) return;

    if (PINC & (1 << PINC0)) {
        game_button1_press();
    } else if (PINC & (1 << PINC1)) {
        game_button2_press();
    }

    game_debounce();
}

// Disable debounce
ISR(TIMER0_COMPA_vect)
{
    game_debounce_active = 0;
    TIMSK0 &= ~(1 << OCIE0A);
}
