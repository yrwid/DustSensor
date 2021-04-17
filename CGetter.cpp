#include "CGetter.hpp"
#include "Serial.hpp"   

CGetter::CGetter()
{}

CGetter& CGetter::getInstance()
{
    // The only instance
    // Guaranteed to be lazy initialized
    // Guaranteed that it will be destroyed correctly
    static CGetter instance;
    return instance;
}

ISerial& getSerialInstance()
{
    return new Serial("/dev/ttyUSB0");
}