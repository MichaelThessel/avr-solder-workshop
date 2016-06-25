#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/delay_basic.h>
#include "ir.h"
#include "hamming74.h"

int ir_buffer;
uint8_t ir_active_flag = 0;
uint8_t ir_offset_delay = 85;
int ir_offset_success = 100;

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

void ir_tx_send(uint8_t data[IR_DATA_SIZE])
{
    uint8_t ir_data[IR_PACKET_SIZE];

    ir_active_flag = 1;

    hamming74_encode(data, ir_data);

    // Send the data
    for (int i = 0; i <= IR_PACKET_SIZE; i++) {
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
    uint8_t ir_data[IR_PACKET_SIZE];
    uint8_t data[IR_DATA_SIZE];

    // Don't receive while transmitting
    if (ir_is_active()) return;

    ir_active_flag = 1;

    // Offset sampling to discard first bit
    ir_offset();

    // Sample every ~100us
    ir_buffer = 0;
    for (int i = 0; i < IR_PACKET_SIZE; i++) {
        ir_buffer = ir_buffer << 1;
        ir_buffer += ((IR_RX_REG_PIN & (1 << IR_RX_PIN_PIN)) >> IR_RX_PIN_PIN) ^ 1;
        _delay_us(97);
    }

    // Copy ir_data into an array
    for (int i = 0; i < IR_PACKET_SIZE; i++) {
        ir_data[i] = (ir_buffer & (1 << i)) ? 1 : 0;
    }

    if (hamming74_decode(ir_data, data)) {
        // Receive data callback
        ir_rx_success(data);
    } else {
        // Adjust the offset dynamically
        ir_offset_adjust();
    }

    ir_active_flag = 0;
}

void ir_offset_adjust()
{
    if (ir_buffer == 0) {
        if (--ir_offset_success > 0) return;

        ir_offset_delay--;
        ir_offset_success = 100;


        if (ir_offset_delay < 83) {
            ir_offset_delay = 88;
        }
    } else if (ir_offset_success < 300) {
        ir_offset_success++;
    }
}

void ir_offset()
{
    // @ 8Mhz, 1 cycle runs 0.125us, _delay_loop_2 takes 4 cyles/count
    // So each count is 0.5us
    _delay_loop_2(ir_offset_delay * 2);
}


// ISR for receive interrupt
ISR(INT1_vect)
{
    cli();
    ir_rx_handle();
    sei();
}
