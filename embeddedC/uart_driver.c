/*
UART (Universal Asynchronous Receiver-Transmitter) is another popular communication protocol used in many embedded systems.

Here's a simplified breakdown of UART communication:

1. **Baud Rate**: This determines the speed of communication. Both devices must agree on this rate.
2. **Start Bit**: Before sending data bits, a start bit (usually `0`) is sent to indicate the beginning of transmission.
3. **Data Bits**: Typically 7 or 8 bits. This is the actual data being transmitted.
4. **Parity Bit**: Used for error checking. It might be even, odd, or none. Both devices must agree on this.
5. **Stop Bit**: After sending data bits, a stop bit (usually `1`) is sent to signify the end of transmission.

Let's look at a simple UART driver to send the string "hello world!".

*/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// Simplified UART configurations
#define UART_BAUD_RATE 9600
#define UART_PARITY_NONE
#define UART_STOP_BIT_ONE
#define UART_DATA_BITS_8

// Pseudo function to initialize UART hardware
void UART_Init(uint32_t baudRate) {
    // Configure UART pins: RX and TX
    // Configure UART registers for the given baud rate
    // Setup data bits, stop bits, and parity
    // Enable the UART module
}

// Pseudo function to send a byte via UART
void UART_SendByte(uint8_t byte) {
    // Wait until UART is ready to send (e.g., check a "ready to send" flag)

    // Send start bit

    // Send data bits (LSB first for typical UARTs)
    for (int i = 0; i < 8; i++) {
        // Set UART TX pin to the bit value
        // Wait for the duration of one bit (depends on baud rate)
        byte >>= 1; // Move to the next bit
    }

    // If using parity, compute and send parity bit

    // Send stop bit
    // Wait for the duration of the stop bit
}

void UART_SendString(const char* str) {
    while (*str) {
        UART_SendByte(*str++);
    }
}

int main() {
    UART_Init(UART_BAUD_RATE);
    UART_SendString("hello world!");

    return 0;
}
```
/*
Here's an explanation of the UART driver:

1. **Initialization (`UART_Init`)**:
    - This function initializes the UART hardware by setting up the RX and TX pins, configuring the UART registers for the desired baud rate, and setting the data bits, stop bits, and parity as required.

2. **Sending a Byte (`UART_SendByte`)**:
    - Before sending, we wait until the UART is ready (checking some hardware flag).
    - The function then sends the start bit, followed by the actual data bits. In many UART systems, data is transmitted LSB (least significant bit) first. 
    - If a parity bit is used, the function computes and sends it.
    - Finally, the function sends the stop bit.

3. **Sending a String (`UART_SendString`)**:
    - This function simply iterates over the string and sends each character byte using the `UART_SendByte` function.

It's worth noting that the above code is a high-level and abstract representation of a UART driver. Actual implementations would be more complex and would need to directly manipulate specific microcontroller registers, handle various edge cases, and potentially deal with interrupts for more efficient communication. This code serves as a starting point to understand the underlying operations of UART communication.
*/
