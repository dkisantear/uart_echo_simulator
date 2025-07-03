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
    // Syntax: const uint8_t *buf means 'pointer to constant unsigned 8-bit integer array'
    // size_t buf_len is the length of the buffer (always non-negative)
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
    // out_buf must have at least len+3 bytes allocated
    out_buf[0] = UART_START_BYTE;
    out_buf[1] = len;
    memcpy(&out_buf[2], data, len);
    out_buf[len + 2] = uart_compute_checksum(len, data);
    return len + 3;
}

// Echo a packet (simulate UART echo)
void uart_echo_packet(const uart_packet_t *packet) {
    // Print the packet as hex bytes
    printf("Echoed packet: ");
    printf("%02X %02X ", packet->start, packet->len);
    for (uint8_t i = 0; i < packet->len; ++i) {
        printf("%02X ", packet->data[i]);
    }
    printf("%02X\n", packet->chk);
} 