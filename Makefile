UART=/dev/ttyUSB0
TYPE=arduino:avr
BOARD=$(TYPE):nano:cpu=atmega328old
BAUDRATE=115200

install:
	arduino-cli core install $(TYPE)

configure:
	arduino-cli core update-index

board_list:
	arduino-cli board list

push:
	arduino-cli compile --fqbn $(BOARD) .
	arduino-cli upload --port $(UART) --fqbn $(BOARD) .

read_uart:
	picocom -b $(BAUDRATE) -r -l $(UART)
