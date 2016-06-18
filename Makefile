BIN=main
OBJS=main.o
SRCS=main.c leds.c ir.c hamming74.c Light_WS2812/light_ws2812.c

MCU=atmega328p
SPEED=8000000UL
LIBS=

CC=avr-gcc
OBJCOPY=avr-objcopy

CFLAGS=-Os -DF_CPU=${SPEED} -mmcu=${MCU} ${LIBS} -std=gnu99

default: build flash

build: ${BIN}.hex

${BIN}.elf: ${SRCS}
	${CC} ${CFLAGS} -o $@ $^

${BIN}.hex: ${BIN}.elf
	${OBJCOPY} -O ihex -R .eeprom $< $@

flash: ${BIN}.hex
	avrdude -F -V -c dragon_isp -p atmega328 -U flash:w:$<

clean:
	rm -f ${BIN}.elf ${BIN}.hex ${OBJS}
