/*
Approach

- We maintain 2 buffers, and keep track of which buffer is active. For every buffer we maintain bool full. 
- We write into active buffer. Once done we set this buffer to full
- We read from inactive buffer. Make sure inactive buffer is full before reading
- I believe we set buffer to full once write is done even if we have space remanining. 
*/

#include <stdio.h>
#include <stdbool.h>

#define BUFFER_SIZE 256

typedef struct {
    int data[BUFFER_SIZE];
    bool full;
} Buffer;

typedef struct {
    Buffer buffers[2];
    int activeBuffer; // 0 or 1
} PingPongBuffer;

void initialize(PingPongBuffer* ppb) {
    ppb->buffers[0].full = false;
    ppb->buffers[1].full = false;
    ppb->activeBuffer = 0;
}

void writeData(PingPongBuffer* ppb, int* data, int size) {
    if (size > BUFFER_SIZE) {
        printf("Data size exceeds buffer capacity.\n");
        return;
    }

    if (ppb->buffers[ppb->activeBuffer].full) {
        // Switch to the other buffer
        ppb->activeBuffer ^= 1;
    }

    for (int i = 0; i < size; i++) {
        ppb->buffers[ppb->activeBuffer].data[i] = data[i];
    }

    ppb->buffers[ppb->activeBuffer].full = true;
}

int* readData(PingPongBuffer* ppb, int* size) {
    int inactiveBuffer = ppb->activeBuffer ^ 1;

    if (!ppb->buffers[inactiveBuffer].full) {
        printf("No data to read from inactive buffer.\n");
        *size = 0;
        return NULL;
    }

    *size = BUFFER_SIZE;
    ppb->buffers[inactiveBuffer].full = false;
    return ppb->buffers[inactiveBuffer].data;
}

int main() {
    PingPongBuffer ppb;
    initialize(&ppb);

    int dataToWrite[BUFFER_SIZE] = {0}; // Dummy data
    for (int i = 0; i < BUFFER_SIZE; i++) {
        dataToWrite[i] = i;
    }

    writeData(&ppb, dataToWrite, BUFFER_SIZE);

    int size;
    int* dataRead = readData(&ppb, &size);
    if (dataRead) {
        // Process the data, example: print first 10 items
        for (int i = 0; i < 10; i++) {
            printf("%d ", dataRead[i]);
        }
        printf("\n");
    }

    return 0;
}

