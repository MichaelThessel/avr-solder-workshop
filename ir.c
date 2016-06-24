#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "ir.h"
#include "hamming74.h"

int ir_buffer;
uint8_t ir_buffer_index = 0;
uint8_t ir_buffer_size = 7;
uint8_t ir_active_flag = 0;

void ir_setup()
{
    IR_TX_SETUP();
    IR_RX_SETUP();
    IR_RX_ENABLE();

    // Set up receive trigger
    EICRA |= (1 << ISC11) | (1 << ISC10); // Trigger interrupt on rising edge of INT1
    EIMSK |= (1 << INT1);

    sei();
}

uint8_t ir_is_active()
{
    return ir_active_flag ? 1 : 0;
}

void ir_tx_send(uint8_t data[4])
{
    uint8_t ir_data[7];

    ir_active_flag = 1;

    hamming74_encode(data, ir_data);

    // Send the data
    for (int i = 0; i < 8; i++) {
        if (i == 0) {
            // Transmissions always start with a 1 bit
            IR_TX_ON();
            _delay_us(30);
            IR_TX_OFF();
            _delay_us(70);
        } else {
            if (ir_data[i - 1]) {
                IR_TX_ON();
                _delay_us(30);
                IR_TX_OFF();
                _delay_us(70);
            } else {
                _delay_us(100);
            }
        }
    }

    ir_active_flag = 0;
}

void ir_rx_handle()
{
    uint8_t ir_data[7];
    uint8_t data[4] = {1, 0, 0, 0};

    // Don't receive while transmitting
    if (ir_is_active()) return;

    ir_active_flag = 1;

    // Offset sampling to discard first bit; 85 has been determined empirically
    _delay_us(85);

    // Sample every ~100us
    ir_buffer = 0;
    for (int i = 0; i < 7; i++) {
        ir_buffer = ir_buffer << 1;
        ir_buffer += ((IR_RX_REG_PIN & (1 << IR_RX_PIN_PIN)) >> IR_RX_PIN_PIN) ^ 1;
        // TODO: add some delta in case Hamming fails frequently
        _delay_us(97);
    }

    // Copy ir_data into an array
    for (int i = 0; i < 7; i++) {
        ir_data[i] = (ir_buffer & (1 << i)) ? 1 : 0;
    }

    hamming74_decode(ir_data, data);

    // TODO: impelment callback

    ir_active_flag = 0;
}

// ISR for receive interrupt
ISR(INT1_vect)
{
    cli();
    ir_rx_handle();
    sei();
}
