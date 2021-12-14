#include "fifobufer.h"
#include <stdio.h>

static void increaseTail(FIFO_TS *const self);
static void increaseHead(FIFO_TS *const self);

void fifoCreate(FIFO_TS *const self, void *const buffer, const uint16_t bufferSize, const uint8_t bufferTypeSize)
{
    self->buffer = buffer;

    self->bufferSize = bufferSize;

    self->bufferTypeSize = bufferTypeSize;

    self->head = 0;

    self->tail = 0;

    self->freeSpace = bufferSize - 1;
}

bool fifoWrite(FIFO_TS *const self, const uint64_t data)
{
    static uint64_t temp = 0;
    temp = data;

    if( isFull(self) == false )
    {
        memcpy((void *)&self->buffer[self->head], &temp, self->bufferTypeSize);
        increaseHead(self);

        return true;
    }
    else{
        return false;
    }
}

bool fifoRead(FIFO_TS *self, void *readData)
{
    if( isEmpty(self) == false )
    {
        memcpy(readData, (void *)&self->buffer[self->tail], self->bufferTypeSize);
        increaseTail(self);
        return 1;
    }
    else{
        return 0;
    }
}

uint16_t getFreeSpace(FIFO_TS *const self)
{
    return self->freeSpace + 1;
}

bool isEmpty(FIFO_TS *const self)
{
    if( getFreeSpace(self) == self->bufferSize )
    {
        return true;
    }
    else{
        return false;
    }
}

bool isFull(FIFO_TS *const self)
{
    if( getFreeSpace(self) - 1 == 0 ){
        return true;
    }else{
        return false;
    }
}

static void increaseTail(FIFO_TS *const self)
{
    self->tail += self->bufferTypeSize;
    self->freeSpace++;

    if( self->tail == (self->bufferSize * self->bufferTypeSize) )
    {
        self->tail = 0;
    }
}

static void increaseHead(FIFO_TS *const self)
{
    self->head += self->bufferTypeSize;
    self->freeSpace--;

    if( self->head == (self->bufferSize * self->bufferTypeSize) )
    {
        self->head = 0;
    }
}

