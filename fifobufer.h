#ifndef FIFOBUFER_H
#define FIFOBUFER_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    uint8_t *buffer;

    uint16_t bufferSize;

    uint8_t bufferTypeSize;

    uint16_t head, tail;

    uint16_t freeSpace;
}FIFO_TS;

void fifoCreate(FIFO_TS *self, void* buffer, uint16_t bufferSize, uint8_t bufferTypeSize);

bool fifoWrite(FIFO_TS *self, const uint64_t data);

bool fifoRead(FIFO_TS *const self, void *readData);

uint16_t getFreeSpace(FIFO_TS *const self);

bool isEmpty(FIFO_TS *self);

bool isFull(FIFO_TS *self);





#endif // FIFOBUFER_H
