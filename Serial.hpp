// /////////////////////////////////////////////////
// // Serial.hpp                                  //
// /////////////////////////////////////////////////

#ifndef SERIAL_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define SERIAL_H

#include <cstddef>
#include "ISerial.hpp"

class Serial : public ISerial
{
private:
    // private fields
    int fd;
    const char* portName;

    // private methods
    void setBlocking(int should_block);

public:
    // public constant 
    static const int baud115200 = 0010002;
    static const int baud9600   = 0000015;

    Serial(const char * const portName);
    ~Serial();
    int setInterfaceAttribs(int speed, int parity) override;
    int writeToSerial(const char* message, size_t len) override;
    int readFromSerial(char* output, size_t len) override;
};

#endif