#include "globals.h"

extern "C"
{
#include "fifobufer.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
}

#if RELEASE == 1

#define USER_CMD_FIFO_BUFFER_SIZE   ( 1024 )
#define AT_CMD_FIFO_BUFFER_SIZE     ( 512 )

FIFO_TS userCMDFifo;
uint8_t userCMDFifoBuffer[USER_CMD_FIFO_BUFFER_SIZE];

FIFO_TS ATCMDFifo;
uint16_t ATCMDFifoBuffer[AT_CMD_FIFO_BUFFER_SIZE];

int main()
{
    uint8_t readingDataU8 = 0;
    uint16_t readingDataU16 = 0;

    fifoCreate(&userCMDFifo, userCMDFifoBuffer, sizeof(userCMDFifoBuffer), sizeof(userCMDFifoBuffer[0]));
    fifoCreate(&ATCMDFifo, ATCMDFifoBuffer, sizeof(ATCMDFifoBuffer), sizeof(ATCMDFifoBuffer[0]));

    /* Uint8_t Example */
    if( true == fifoWrite(&userCMDFifo, 0x10))
    {
        printf("Writing is successful\n");
    }
    else{
        printf("Writing is not successful\n");
    }

    if( true == fifoRead(&userCMDFifo, &readingDataU8))
    {
        printf("Reading is successful\t");
        printf("Reading data : %d\n", readingDataU8);
    }
    else{
        printf("Reading is not successful\n");
    }

    /* Uint16_t Example */
    if( true == fifoWrite(&ATCMDFifo, 300))
    {
        printf("Writing is successful\n");
    }
    else{
        printf("Writing is not successful\n");
    }

    if( true == fifoRead(&ATCMDFifo, &readingDataU16))
    {
        printf("Reading is successful\t");
        printf("Reading data : %d\n", readingDataU16);
    }
    else{
        printf("Reading is not successful\n");
    }

    static int i = 0;

    i = 0;
    while( fifoWrite(&ATCMDFifo, i) == true )
    {
        i++;
    }

    i = 0;
    while( fifoRead(&ATCMDFifo, &readingDataU16) == true )
    {
        i++;
        printf("Index : %d, Data : %d\n", i, readingDataU16 );
    }

    return 0;
}


#elif UNIT_TEST == 1
#include "iostream"
#include <CppUTest/CommandLineTestRunner.h>

using namespace std;

int main(int ac, char** av)
{
    return CommandLineTestRunner::RunAllTests(ac, av);
}

#endif


