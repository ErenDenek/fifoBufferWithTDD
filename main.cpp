#include "globals.h"

extern "C"
{
    #include "fifobufer.h"
}

#if RELEASE == 1
#include <iostream>

#define USER_CMD_FIFO_BUFFER_SIZE  1024

FIFO_TS userCMDFifo;
uint8_t userCMDFifoBuffer[USER_CMD_FIFO_BUFFER_SIZE];

int main()
{
    fifoCreate(&userCMDFifo, userCMDFifoBuffer, sizeof(userCMDFifoBuffer), sizeof(userCMDFifoBuffer[0]));
    std::cout << "ereh";
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


