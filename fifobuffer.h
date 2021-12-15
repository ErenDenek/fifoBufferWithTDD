#ifndef FIFOBUFFER_H
#define FIFOBUFFER_H

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

void fifoCreate(FIFO_TS *const self, void *const buffer, const uint16_t bufferSize, const uint8_t bufferTypeSize);

bool fifoWrite(FIFO_TS *self, const uint64_t data);

bool fifoRead(FIFO_TS *const self, void *readData);

bool fifoIsEmpty(const FIFO_TS *const self);

bool fifoIsFull(const FIFO_TS *const self);

uint16_t fifoGetFreeSpace(const FIFO_TS *const self);

#endif // FIFOBUFFER_H
