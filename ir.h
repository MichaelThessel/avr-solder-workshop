#ifndef __ir_h_included__
#define __ir_h_included__

#include "macros.h"

#define IR_CFG_PORT_NAME    D
#define IR_CFG_TX_BIT       2

#define IR_TX_REG_PORT  CONC_REG_PORT(IR_CFG_PORT_NAME)
#define IR_TX_REG_DDR   CONC_REG_DDR(IR_CFG_PORT_NAME)
#define IR_TX_REG_PIN   CONC_REG_PIN(IR_CFG_PORT_NAME)

#define IR_TX_PIN_PORT  CONC_PIN_PORT(IR_CFG_PORT_NAME, IR_CFG_TX_BIT)
#define IR_TX_PIN_DDR   CONC_PIN_DDR(IR_CFG_PORT_NAME, IR_CFG_TX_BIT)
#define IR_TX_PIN_PIN   CONC_PIN_PIN(IR_CFG_PORT_NAME, IR_CFG_TX_BIT)

#define IR_TX_ENABLE()  (IR_TX_REG_DDR |= (1 << IR_TX_PIN_DDR))
#define IR_LED_ON()  (IR_TX_REG_PORT |= (1 << IR_TX_PIN_PORT))
#define IR_LED_OFF()  (IR_TX_REG_PORT &= ~(1 << IR_TX_PIN_PORT))


/*
 * Setup
 */
void ir_setup();

#endif
