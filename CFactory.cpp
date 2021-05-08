#include "CFactory.hpp"
#include "Serial.hpp"   
#include "SensorReader.hpp"
#include "SignalSetter.hpp"

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

ISerial* CFactory::getSerialInstance(const char* devName, const int baud, int isBlocking)
{
    return new Serial(devName, baud, isBlocking);
}

ISensorReader* CFactory::getSensorReaderInstance(ISerial* serialPort)
{
    return new SensorReader(serialPort);
}

void CFactory::enableSignal()
{
    signalObj = new SignalSetter();
}