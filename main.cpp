#include "globals.h"

extern "C"
{
#include "fifobufer.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
}

#if RELEASE == 1

#define USER_CMD_FIFO_BUFFER_SIZE  1024

FIFO_TS userCMDFifo;
uint8_t userCMDFifoBuffer[USER_CMD_FIFO_BUFFER_SIZE];

int main()
{
    uint8_t readingDataU8 = 0;

    fifoCreate(&userCMDFifo, userCMDFifoBuffer, sizeof(userCMDFifoBuffer), sizeof(userCMDFifoBuffer[0]));

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


