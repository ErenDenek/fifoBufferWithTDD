TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        fifobuffer.c \
        main.cpp \
        unitTests/fifoBufferTests.cpp



HEADERS += \
    fifobuffer.h \
    globals.h


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../ARSIS-SW/Software/trunk/main/Test/cpputest-3.8/x64/release/ -lCppUTestd
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../ARSIS-SW/Software/trunk/main/Test/cpputest-3.8/x64/debug/ -lCppUTestd

INCLUDEPATH += $$PWD/../../../../../ARSIS-SW/Software/trunk/main/Test/cpputest-3.8/include
DEPENDPATH += $$PWD/../../../../../ARSIS-SW/Software/trunk/main/Test/cpputest-3.8/include
