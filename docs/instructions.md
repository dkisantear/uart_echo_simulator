# UART Echo Simulator

## Objective
Simulate a basic UART communication interface in C. Accept user input as a packet, parse it, then echo the same packet back.

## Feature Checklist
- [ ] Define packet format (e.g., [START][LEN][DATA][CHK])
- [ ] Write `uart.h` with function declarations
- [ ] Implement `uart.c` to simulate receiving + echoing packets
- [ ] In `main.c`, simulate sending test packets via stdin
- [ ] Add error detection for invalid packets
- [ ] Print parsed data to terminal

## Stretch Goals
- [ ] Implement ring buffer for RX
- [ ] Threading simulation for UART RX/processing 