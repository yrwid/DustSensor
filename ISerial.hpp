
#ifndef IF_SERIAL_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define IF_SERIAL_H

#include <cstddef>

class ISerial
{
    public:
        // public constant 
        static const int baud115200 = 0010002;
        static const int baud9600   = 0000015;

        virtual ~ISerial() {}
        virtual bool setUsbDev(const char * const) = 0;
        virtual int setInterfaceAttribs(int, int) = 0;
        virtual int writeToSerial(const char*, size_t) = 0;
        virtual int readFromSerial(char*, size_t) = 0;
};

#endif