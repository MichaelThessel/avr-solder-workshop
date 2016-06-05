/*
 * Port & Pin Mapping macros
 */
#ifndef __macros_h_included__
#define __macros_h_included__

#define CON(a, b)      a ## b
#define CONC(a, b)     CON(a, b)

#define CONC_REG_PORT(port)     CONC(PORT, port)
#define CONC_REG_DDR(port)      CONC(DDR, port)
#define CONC_REG_PIN(port)      CONC(PIN, port)

#define CONC_PIN_PORT(port, pin)    CONC(PORT, CONC(port, pin))
#define CONC_PIN_DDR(port, pin)     CONC(DD, CONC(port, pin))
#define CONC_PIN_PIN(port, pin)     CONC(PIN, CONC(port, pin))

#endif
