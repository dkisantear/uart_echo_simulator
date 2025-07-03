# Testing Your UART Simulator Online

Since we're having trouble with the local C compiler installation, let's test your code online first!

## Option 1: OnlineGDB (Recommended)
1. Go to https://www.onlinegdb.com/
2. Click "Language" dropdown and select "C"
3. Copy and paste your code files:

### Step 1: Copy uart.h content
```c
#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <stdbool.h>

// Packet format: [START][LEN][DATA][CHK]
#define UART_START_BYTE 0xAA
#define UART_MAX_DATA_LEN 256

// UART packet structure
typedef struct {
    uint8_t start;
    uint8_t len;
    uint8_t data[UART_MAX_DATA_LEN];
    uint8_t chk;
} uart_packet_t;

// Parse a raw buffer into a uart_packet_t. Returns true if valid, false if error.
bool uart_parse_packet(const uint8_t *buf, size_t buf_len, uart_packet_t *packet);

// Build a packet from data and compute checksum. Returns length of packet in bytes.
size_t uart_build_packet(const uint8_t *data, uint8_t len, uint8_t *out_buf);

// Echo a packet (simulate UART echo)
void uart_echo_packet(const uart_packet_t *packet);

// Compute checksum for a packet (LEN + DATA bytes modulo 256)
uint8_t uart_compute_checksum(uint8_t len, const uint8_t *data);

#endif // UART_H
```

### Step 2: Copy uart.c content
```c
#include "uart.h"
#include <stdio.h>
#include <string.h>

// Compute checksum: (LEN + sum(DATA bytes)) % 256
uint8_t uart_compute_checksum(uint8_t len, const uint8_t *data) {
    uint16_t sum = len;
    for (uint8_t i = 0; i < len; ++i) {
        sum += data[i];
    }
    return (uint8_t)(sum % 256);
}

// Parse a raw buffer into a uart_packet_t. Returns true if valid, false if error.
bool uart_parse_packet(const uint8_t *buf, size_t buf_len, uart_packet_t *packet) {
    if (buf_len < 4) return false; // Minimum packet size
    if (buf[0] != UART_START_BYTE) return false; // Check start byte
    uint8_t len = buf[1];
    if (buf_len < (size_t)(len + 3)) return false; // Not enough data
    uint8_t chk = buf[len + 2];
    uint8_t calc_chk = uart_compute_checksum(len, &buf[2]);
    if (chk != calc_chk) return false; // Checksum mismatch
    // Fill packet struct
    packet->start = buf[0];
    packet->len = len;
    memcpy(packet->data, &buf[2], len);
    packet->chk = chk;
    return true;
}

// Build a packet from data and compute checksum. Returns length of packet in bytes.
size_t uart_build_packet(const uint8_t *data, uint8_t len, uint8_t *out_buf) {
    out_buf[0] = UART_START_BYTE;
    out_buf[1] = len;
    memcpy(&out_buf[2], data, len);
    out_buf[len + 2] = uart_compute_checksum(len, data);
    return len + 3;
}

// Echo a packet (simulate UART echo)
void uart_echo_packet(const uart_packet_t *packet) {
    printf("Echoed packet: ");
    printf("%02X %02X ", packet->start, packet->len);
    for (uint8_t i = 0; i < packet->len; ++i) {
        printf("%02X ", packet->data[i]);
    }
    printf("%02X\n", packet->chk);
}
```

### Step 3: Copy main.c content
```c
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "uart.h"

// Helper to read a line of input and remove newline
void read_line(char *buf, size_t max_len) {
    if (fgets(buf, (int)max_len, stdin)) {
        size_t len = strlen(buf);
        if (len > 0 && buf[len-1] == '\n') buf[len-1] = '\0';
    }
}

int main() {
    char input[UART_MAX_DATA_LEN + 1]; // +1 for null terminator
    printf("Enter data to send (max %d chars): ", UART_MAX_DATA_LEN);
    read_line(input, sizeof(input));
    uint8_t data[UART_MAX_DATA_LEN];
    uint8_t len = (uint8_t)strlen(input);
    memcpy(data, input, len);
    uint8_t packet_buf[UART_MAX_DATA_LEN + 3]; // [START][LEN][DATA][CHK]
    size_t packet_size = uart_build_packet(data, len, packet_buf);
    printf("Built packet: ");
    for (size_t i = 0; i < packet_size; ++i) {
        printf("%02X ", packet_buf[i]);
    }
    printf("\n");
    // Simulate receiving the packet
    uart_packet_t packet;
    if (uart_parse_packet(packet_buf, packet_size, &packet)) {
        printf("Packet parsed successfully! Data: ");
        for (uint8_t i = 0; i < packet.len; ++i) {
            printf("%c", packet.data[i]);
        }
        printf("\n");
        uart_echo_packet(&packet);
    } else {
        printf("Invalid packet received!\n");
    }
    return 0;
}
```

### Step 4: Test it!
1. Click "Run" button
2. Type something like "Hello World" when prompted
3. See your UART packet in action!

## What You Should See
When you type "Hello", you should see output like:
```
Enter data to send (max 256 chars): Hello
Built packet: AA 05 48 65 6C 6C 6F 8A
Packet parsed successfully! Data: Hello
Echoed packet: AA 05 48 65 6C 6C 6F 8A
```

This shows:
- AA = Start byte (170)
- 05 = Length (5 characters)
- 48 65 6C 6C 6F = ASCII for "Hello"
- 8A = Checksum

Try it and let me know what happens! 