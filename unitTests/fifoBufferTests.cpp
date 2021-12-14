#include <CppUTest/TestHarness.h>
#include <iostream>

using namespace std;
extern "C"
{
    #include "fifobufer.h"
}

FIFO_TS fifo;
uint8_t fifoBuffer[16];


TEST_GROUP(fifo)
{
    void setup()
    {
        fifoCreate(&fifo, fifoBuffer, sizeof (fifoBuffer), sizeof (fifoBuffer[0]));
    }
    void teardown()
    {

    }
};

TEST(fifo, fifoCreatedControl)
{
    CHECK_EQUAL( sizeof (fifoBuffer), getFreeSpace(&fifo));
    CHECK_EQUAL( false ,isFull(&fifo));
    CHECK_EQUAL( true ,isEmpty(&fifo));
    CHECK_EQUAL( 16, getFreeSpace(&fifo));
}

TEST(fifo, fifoSingleWriteAndRead)
{
    uint8_t data = 0;

    fifoWrite(&fifo, 10);
    fifoRead(&fifo, &data);

    CHECK_EQUAL(10, data);
    CHECK_EQUAL( false ,isFull(&fifo));
    CHECK_EQUAL( true ,isEmpty(&fifo));
    CHECK_EQUAL( 16, getFreeSpace(&fifo));
}

TEST(fifo, fifoIsEmpty)
{
    uint8_t data;

    fifoWrite(&fifo, 10);
    CHECK_EQUAL(0, isEmpty(&fifo));

    fifoRead(&fifo, &data);
    CHECK_EQUAL(1, isEmpty(&fifo));
}

TEST(fifo, fifoIsFull)
{
    fifoWrite(&fifo, 10);
    CHECK_EQUAL(0, isFull(&fifo));

}

TEST(fifo, fifoFillAllBufferAfterFifoIsFull)
{
    for(uint16_t i = 0; i < fifo.bufferSize; i++ )
    {
        fifoWrite(&fifo, i);
        cout << fifoBuffer[i] << "\n";
    }

    CHECK_EQUAL( false ,fifoWrite(&fifo, 10));
}

TEST(fifo, fifoReadingFromFullBuffer)
{
    uint8_t data = 0;

    for(uint16_t i = 0; i < fifo.bufferSize; i++ )
    {
        fifoWrite(&fifo, i);
        cout << fifoBuffer[i] << "\n";
    }

    fifoRead(&fifo, &data);

    CHECK_EQUAL( false ,isFull(&fifo));
    CHECK_EQUAL( false ,isEmpty(&fifo));
}

TEST(fifo, fifoFullWriteAfterFullRead)
{
    uint8_t data = 0;

    for(uint16_t i = 0; i < fifo.bufferSize; i++ )
    {
        fifoWrite(&fifo, i);
    }

    CHECK_EQUAL( true ,isFull(&fifo));
    CHECK_EQUAL( false ,isEmpty(&fifo));
    CHECK_EQUAL( 0, getFreeSpace(&fifo));

    for(uint16_t i = 0; i < fifo.bufferSize; i++ )
    {
        fifoRead(&fifo, &data);
        CHECK_EQUAL(i, data);
    }

    CHECK_EQUAL( false ,isFull(&fifo));
    CHECK_EQUAL( true ,isEmpty(&fifo));
    CHECK_EQUAL( 16, getFreeSpace(&fifo));
}
