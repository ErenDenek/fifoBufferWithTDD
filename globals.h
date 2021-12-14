#ifndef GLOBALS_H
#define GLOBALS_H

#define UNIT_TEST   0

#if UNIT_TEST == 1
    #define RELEASE 0
#else
    #define RELEASE 1
#endif

#endif // GLOBALS_H
