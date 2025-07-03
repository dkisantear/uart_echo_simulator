# UART Echo Simulator

A C-based simulation of UART (Universal Asynchronous Receiver-Transmitter) communication that demonstrates packet formatting, error detection, and echo functionality.

## Overview

This project simulates a basic UART communication interface where:
- User input is formatted into packets with start byte, length, data, and checksum
- Packets are parsed and validated for integrity
- Valid packets are echoed back to demonstrate the communication loop

## Packet Format

The simulator uses a simple packet format: `[START][LEN][DATA][CHK]`

- **START**: 1 byte (0xAA) - Marks the beginning of a packet
- **LEN**: 1 byte - Number of data bytes
- **DATA**: N bytes - Actual payload (N = LEN)
- **CHK**: 1 byte - Checksum (LEN + sum of DATA bytes) % 256

### Example Packet
For the string "Hello":
```
AA 05 48 65 6C 6C 6F 8A
│   │  │              │
│   │  └─ ASCII "Hello" ─┘
│   └─ Length (5) ─┘
└─ Start byte (0xAA) ─┘
```

## Features

- ✅ Packet format definition with start byte, length, data, and checksum
- ✅ UART header file with function declarations
- ✅ UART implementation for packet parsing and building
- ✅ Main program for simulating packet transmission
- ✅ Error detection for invalid packets
- ✅ Terminal output showing parsed data and packet details
- ✅ Cross-platform compilation (Windows WSL/Ubuntu)

## Project Structure

```
uart_echo_simulator/
├── src/
│   ├── uart.h          # Header file with packet struct and function declarations
│   ├── uart.c          # UART implementation (parsing, building, checksum)
│   └── main.c          # Main program and user interface
├── docs/
│   ├── instructions.md # Project specifications and checklist
│   └── test_online.md  # Guide for online testing
├── DEV_LOG.md          # Development log and progress tracking
├── Makefile            # Build configuration
├── .gitignore          # Git ignore rules
└── README.md           # This file
```

## Installation & Usage

### Prerequisites
- GCC compiler (tested with Ubuntu 13.3.0)
- WSL (Windows Subsystem for Linux) or Linux environment

### Compilation
```bash
# Navigate to project directory
cd uart_echo_simulator

# Compile the program
gcc -Wall -Wextra -std=c99 -o uart_echo_simulator src/main.c src/uart.c
```

### Running
```bash
# Execute the program
./uart_echo_simulator

# Example session:
Enter data to send (max 256 chars): Hello World
Built packet: AA 0B 48 65 6C 6C 6F 20 57 6F 72 6C 64 8F
Packet parsed successfully! Data: Hello World
Echoed packet: AA 0B 48 65 6C 6C 6F 20 57 6F 72 6C 64 8F
```

## Technical Details

### Error Detection
The simulator validates packets by checking:
1. Minimum packet size (4 bytes)
2. Correct start byte (0xAA)
3. Sufficient data length
4. Valid checksum

### Checksum Algorithm
```c
checksum = (LEN + sum of all DATA bytes) % 256
```

### Key Functions
- `uart_build_packet()` - Creates packets from raw data
- `uart_parse_packet()` - Validates and parses received packets
- `uart_compute_checksum()` - Calculates packet checksum
- `uart_echo_packet()` - Displays packet contents

## Development

This project was developed as a learning exercise for:
- C programming fundamentals
- UART communication protocols
- Packet formatting and error detection
- Cross-platform development with WSL

## Future Enhancements

Potential stretch goals:
- [ ] Ring buffer implementation for RX
- [ ] Threading simulation for UART RX/processing
- [ ] Multiple packet types support
- [ ] Real-time packet visualization
- [ ] Network socket simulation

## License

This project is open source and available under the MIT License.

---

**Created by:** [Your Name]  
**Date:** July 2025  
**Purpose:** Educational project for learning UART communication and C programming 