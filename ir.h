#ifndef __ir_h_included__
#define __ir_h_included__

#include "macros.h"

/*
 * Configure pins
 */
#define IR_CFG_TX_PORT      D
#define IR_CFG_TX_PIN       2
#define IR_CFG_SHDN_PORT    D
#define IR_CFG_SHDN_PIN     6

/*
 * Pin & Port definition macros
 */
#define IR_TX_REG_PORT  CONC_REG_PORT(IR_CFG_TX_PORT)
#define IR_TX_REG_DDR   CONC_REG_DDR(IR_CFG_TX_PORT)
#define IR_TX_REG_PIN   CONC_REG_PIN(IR_CFG_TX_PORT)
#define IR_TX_PIN_PORT  CONC_PIN_PORT(IR_CFG_TX_PORT, IR_CFG_TX_PIN)
#define IR_TX_PIN_DDR   CONC_PIN_DDR(IR_CFG_TX_PORT, IR_CFG_TX_PIN)
#define IR_TX_PIN_PIN   CONC_PIN_PIN(IR_CFG_TX_PORT, IR_CFG_TX_PIN)

#define IR_SHDN_REG_PORT  CONC_REG_PORT(IR_CFG_SHDN_PORT)
#define IR_SHDN_REG_DDR   CONC_REG_DDR(IR_CFG_SHDN_PORT)
#define IR_SHDN_REG_PIN   CONC_REG_PIN(IR_CFG_SHDN_PORT)
#define IR_SHDN_PIN_PORT  CONC_PIN_PORT(IR_CFG_SHDN_PORT, IR_CFG_SHDN_PIN)
#define IR_SHDN_PIN_DDR   CONC_PIN_DDR(IR_CFG_SHDN_PORT, IR_CFG_SHDN_PIN)
#define IR_SHDN_PIN_PIN   CONC_PIN_PIN(IR_CFG_SHDN_PORT, IR_CFG_SHDN_PIN)

/*
 * Macros
 */
#define IR_TX_SETUP()  (IR_TX_REG_DDR |= (1 << IR_TX_PIN_DDR))
#define IR_TX_ON()  (IR_TX_REG_PORT |= (1 << IR_TX_PIN_PORT))
#define IR_TX_OFF()  (IR_TX_REG_PORT &= ~(1 << IR_TX_PIN_PORT))

#define IR_RX_ENABLE() ((IR_SHDN_REG_DDR |= (1 << IR_SHDN_PIN_DDR)), \
                        (IR_SHDN_REG_PORT |= (1 << IR_SHDN_PIN_PORT)))

/*
 * Setup
 */
void ir_setup();

#endif
