# UART Echo Simulator

A simple C project to simulate UART (serial) communication and packet handling.

## What is this?
This program lets you type a message, turns it into a UART-style packet, checks it, and echoes it back. It's a personal summer project to learn about reading, writing, and buffering data in C.

## Packet Format
- [START] 1 byte: 0xAA (marks start)
- [LEN]   1 byte: number of data bytes
- [DATA]  N bytes: your message
- [CHK]   1 byte: checksum = (LEN + sum(DATA)) % 256

Example for "Hi":
```
AA 02 48 69 B3
```
- AA = start
- 02 = length
- 48 69 = 'H' 'i' in ASCII
- B3 = checksum

## How to Build and Run
1. Open a terminal in this folder
2. Run:
   ```sh
   gcc -Wall -Wextra -std=c99 -o uart_echo_simulator src/main.c src/uart.c
   ./uart_echo_simulator
   ```
3. Type a message and see the packet breakdown

## Files
- `src/uart.h`   — Packet struct and function declarations
- `src/uart.c`   — Packet logic (build, parse, checksum)
- `src/main.c`   — User input and echo logic
- `Makefile`     — (Optional) For building with `make`
- `DEV_LOG.md`   — My notes and progress
- `docs/`        — Instructions and online test guide

## Features
- Packet creation and parsing
- Error checking (start byte, length, checksum)
- Shows packet bytes and parsed message
- Cross-platform (tested on WSL/Ubuntu)

## Why I Made This
Created by Dominique Kisantear on July 2, 2025.
Personal summer project to understand how data is read, written, and stored in a buffer in C. 