#include "CFactory.hpp"
#include "Serial.hpp"   
#include "SensorReader.hpp"

CFactory::CFactory()
{}

CFactory& CFactory::getInstance()
{
    // The only instance
    // Guaranteed to be lazy initialized
    // Guaranteed that it will be destroyed correctly
    static CFactory instance;
    return instance;
}

ISerial* CFactory::getSerialInstance()
{
    return new Serial();
}

ISensorReader* CFactory::getSensorReaderInstance(ISerial* serialPort)
{
    return new SensorReader(serialPort);
}