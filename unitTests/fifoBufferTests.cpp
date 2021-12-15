#include <CppUTest/TestHarness.h>

extern "C"
{
#include "fifobuffer.h"
#include "stdio.h"
}

FIFO_TS fifoU8;
uint8_t fifoBufferU8[16];

FIFO_TS fifoU16;
uint16_t fifoBufferU16[32];

TEST_GROUP(fifo)
{
    void setup()
    {
        fifoCreate(&fifoU8, fifoBufferU8, sizeof (fifoBufferU8)/sizeof(fifoBufferU8[0]), sizeof (fifoBufferU8[0]));
        fifoCreate(&fifoU16, fifoBufferU16, sizeof (fifoBufferU16)/sizeof (fifoBufferU16[0]), sizeof (fifoBufferU16[0]));
    }
    void teardown()
    {

    }
};

TEST(fifo, fifoCreatedControl)
{
    CHECK_EQUAL( sizeof (fifoBufferU8)/sizeof(fifoBufferU8[0]), fifoU8.bufferSize);
    CHECK_EQUAL( false ,fifoIsFull(&fifoU8));
    CHECK_EQUAL( true ,fifoIsEmpty(&fifoU8));
    CHECK_EQUAL( 16, fifoGetFreeSpace(&fifoU8));

    CHECK_EQUAL( sizeof (fifoBufferU16)/sizeof (fifoBufferU16[0]), fifoU16.bufferSize);
    CHECK_EQUAL( false ,fifoIsFull(&fifoU16));
    CHECK_EQUAL( true ,fifoIsEmpty(&fifoU16));
    CHECK_EQUAL( 32, fifoGetFreeSpace(&fifoU16));
}

TEST(fifo, fifoSingleWriteAndRead)
{
    uint8_t dataU8 = 0;

    fifoWrite(&fifoU8, 10);
    fifoRead(&fifoU8, &dataU8);

    CHECK_EQUAL(10, dataU8);
    CHECK_EQUAL( false ,fifoIsFull(&fifoU8));
    CHECK_EQUAL( true ,fifoIsEmpty(&fifoU8));
    CHECK_EQUAL( 16, fifoGetFreeSpace(&fifoU8));

    uint8_t dataU16 = 0;

    fifoWrite(&fifoU16, 10);
    fifoRead(&fifoU16, &dataU16);

    CHECK_EQUAL(10, dataU16);
    CHECK_EQUAL( false ,fifoIsFull(&fifoU16));
    CHECK_EQUAL( true ,fifoIsEmpty(&fifoU16));
    CHECK_EQUAL( 32, fifoGetFreeSpace(&fifoU16));
}

TEST(fifo, fifoIsEmpty)
{
    uint8_t dataU8;

    fifoWrite(&fifoU8, 10);
    CHECK_EQUAL(0, fifoIsEmpty(&fifoU8));

    fifoRead(&fifoU8, &dataU8);
    CHECK_EQUAL(1, fifoIsEmpty(&fifoU8));

    uint8_t dataU16;

    fifoWrite(&fifoU16, 10);
    CHECK_EQUAL(0, fifoIsEmpty(&fifoU16));

    fifoRead(&fifoU16, &dataU16);
    CHECK_EQUAL(1, fifoIsEmpty(&fifoU16));
}

TEST(fifo, fifoIsFull)
{
    fifoWrite(&fifoU8, 10);
    CHECK_EQUAL(0, fifoIsFull(&fifoU8));

    fifoWrite(&fifoU16, 10);
    CHECK_EQUAL(0, fifoIsFull(&fifoU16));

}

TEST(fifo, fifoFillAllBufferAfterFifoIsFull)
{
    while( fifoGetFreeSpace(&fifoU8) - 1 != 0 )
    {
        static int i = 0;
        fifoWrite( &fifoU8, i++ );
    }

    CHECK_EQUAL( false ,fifoWrite(&fifoU8, 10));

    while( fifoGetFreeSpace(&fifoU16) - 1 != 0 )
    {
        static int i = 0;
        fifoWrite( &fifoU16, i++ );
    }

    CHECK_EQUAL( false ,fifoWrite(&fifoU16, 10));
}

TEST(fifo, fifoReadingFromFullBuffer)
{
    uint8_t dataU8 = 0;

    while( fifoGetFreeSpace(&fifoU8) - 1 != 0 )
    {
        static int i = 0;
        fifoWrite( &fifoU8, i++ );
    }

    fifoRead(&fifoU8, &dataU8);

    CHECK_EQUAL( false ,fifoIsFull(&fifoU8));
    CHECK_EQUAL( false ,fifoIsEmpty(&fifoU8));

    uint8_t dataU16 = 0;

    while( fifoGetFreeSpace(&fifoU16) - 1 != 0 )
    {
        static int i = 0;
        fifoWrite( &fifoU16, i++ );
    }

    fifoRead(&fifoU16, &dataU16);

    CHECK_EQUAL( false ,fifoIsFull(&fifoU16));
    CHECK_EQUAL( false ,fifoIsEmpty(&fifoU16));
}

TEST(fifo, fifoFullWriteAfterFullRead)
{
    uint8_t dataU8 = 0;
    static int i = 0;

    i = 0;
    while( fifoWrite(&fifoU8, i) == true )
    {
        i++;
    }

    CHECK_EQUAL( true ,fifoIsFull(&fifoU8));
    CHECK_EQUAL( false ,fifoIsEmpty(&fifoU8));
    CHECK_EQUAL( 0, fifoGetFreeSpace(&fifoU8) - 1);

    i = 0;
    while( fifoRead(&fifoU8, &dataU8) == true )
    {
        i++;
    }

    CHECK_EQUAL( false ,fifoIsFull(&fifoU8));
    CHECK_EQUAL( true ,fifoIsEmpty(&fifoU8));
    CHECK_EQUAL( 16, fifoGetFreeSpace(&fifoU8));

    uint16_t dataU16 = 0;

    i = 0;
    while( fifoWrite(&fifoU16, i) == true )
    {
        i++;
    }

    CHECK_EQUAL( true ,fifoIsFull(&fifoU16));
    CHECK_EQUAL( false ,fifoIsEmpty(&fifoU16));

    i = 0;
    while( fifoRead(&fifoU16, &dataU16) == true )
    {
        i++;
    }

    CHECK_EQUAL( false ,fifoIsFull(&fifoU16));
    CHECK_EQUAL( true ,fifoIsEmpty(&fifoU16));
    CHECK_EQUAL( 32, fifoGetFreeSpace(&fifoU16));
}
