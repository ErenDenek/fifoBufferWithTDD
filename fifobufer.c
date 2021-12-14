#include "fifobufer.h"

static void increaseTail(FIFO_TS *const self);
static void increaseHead(FIFO_TS *const self);

void fifoCreate(FIFO_TS *self, void* buffer, uint16_t bufferSize, uint8_t bufferTypeSize)
{
    self->buffer = buffer;

    self->bufferSize = bufferSize;

    self->bufferTypeSize = bufferTypeSize;

    self->head = 0;

    self->tail = 0;

    self->freeSpace = bufferSize;
}

bool fifoWrite(FIFO_TS *self, const uint64_t data)
{
    uint64_t temp = data;

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

bool fifoRead(FIFO_TS *const self, void *readData)
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
    return self->freeSpace;
}

bool isEmpty(FIFO_TS *self)
{
    if( self->freeSpace == self->bufferSize )
    {
        return true;
    }
    else{
        return false;
    }
}

bool isFull(FIFO_TS *self)
{
    if( self->freeSpace == 0 ){
        return true;
    }else{
        return false;
    }
}

static void increaseTail(FIFO_TS *const self)
{
    self->tail += self->bufferTypeSize;
    self->freeSpace += self->bufferTypeSize;

    if( self->tail == self->bufferSize )
    {
        self->tail = 0;
    }
}

static void increaseHead(FIFO_TS *const self)
{
    self->head += self->bufferTypeSize;
    self->freeSpace -= self->bufferTypeSize;

    if( self->head == self->bufferSize )
    {
        self->head = 0;
    }
}

