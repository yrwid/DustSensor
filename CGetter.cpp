#include "CGetter.hpp"
#include "Serial.hpp"   
#include "SensorReader.hpp"

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

ISensorReader* CGetter::getSensorReaderInstance(ISerial* serialPort)
{
    return new SensorReader(serialPort);
}