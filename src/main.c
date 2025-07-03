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
