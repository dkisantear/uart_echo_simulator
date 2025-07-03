CC=gcc
CFLAGS=-Wall -Wextra -std=c99
SRC=src/main.c src/uart.c
OUT=uart_echo_simulator

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC)

clean:
	rm -f $(OUT) *.o 