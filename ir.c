#include <avr/io.h>
#include <avr/interrupt.h>
#include "ir.h"
#include "hamming74.h"

uint8_t ir_buffer[7];
uint8_t ir_buffer_size = 7;
uint8_t ir_buffer_index = 0;
uint8_t ir_has_data = 0;

void ir_setup()
{
    IR_TX_SETUP();
    IR_RX_SETUP();
    IR_RX_ENABLE();

    sei();
}

void ir_tx_init()
{
    TCCR1B |= (1 << WGM12); // Configure timer 1 for CTC mode
    TIMSK1 |= (1 << OCIE1A); // Enable CTC interrupt
    TCCR1B |= (1 << CS10); // No prescaler
    sei();
    OCR1A = 0x50; // Trigger ISR every 20us
}

uint8_t ir_tx_active()
{
    return ir_has_data ? 1 : 0;
}

void ir_tx_send(uint8_t data[4])
{
    ir_has_data = 1;

    hamming74_encode(data, ir_buffer);
}

void ir_tx_handle()
{
    if (!ir_has_data) return;

    if (ir_buffer_index < ir_buffer_size) {
        if (ir_buffer[ir_buffer_index]) {
            IR_TX_REG_PORT |= (1 << IR_TX_PIN_PORT);
        } else {
            IR_TX_REG_PORT &= ~(1 << IR_TX_PIN_PORT);
        }

        ir_buffer_index++;
    } else {
        ir_buffer_index = 0;
        ir_has_data = 0;
        IR_TX_REG_PORT &= ~(1 << IR_TX_PIN_PORT);
    }
}

ISR(TIMER1_COMPA_vect)
{
    ir_tx_handle();
}
