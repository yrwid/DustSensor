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

ISerial* CGetter::getSerialInstance()
{
    return new Serial();
}