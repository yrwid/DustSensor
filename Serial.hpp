// /////////////////////////////////////////////////
// // Serial.hpp                                  //
// /////////////////////////////////////////////////

#ifndef SERIAL_H
#define SERIAL_H

#include <cstddef>
#include "ISerial.hpp"

class Serial : public ISerial
{
private:
    // private fields
    int m_FD;
    const char* m_pPortName;

    // private methods
    void setBlocking(int should_block);

public:
    Serial();
    ~Serial();
    virtual bool setUsbDev(const char * const portName) override;
    virtual int setInterfaceAttribs(int speed, int parity) override;
    virtual int writeToSerial(const char* message, size_t len) override;
    virtual int readFromSerial(char* output, size_t len) override;
    virtual void flushPortBuffer() override;
};

#endif