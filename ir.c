#include <avr/io.h>
#include "ir.h"

void ir_setup()
{
    IR_TX_SETUP();
    IR_RX_ENABLE();
}
