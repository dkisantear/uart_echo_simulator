#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

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