
#ifndef IF_SERIAL_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define IF_SERIAL_H

#include <cstddef>

class ISerial
{
    public:
        virtual ~ISerial() {}
        virtual int setInterfaceAttribs(int, int) = 0;
        virtual int writeToSerial(const char*, size_t) = 0;
        virtual int readFromSerial(char*, size_t) = 0;
};

#endif