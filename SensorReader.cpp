#include "SensorReader.hpp"
#include <unistd.h>

SensorReader::SensorReader( ISerial* pSerial ) : m_pSerialPort( pSerial )
{    
}

bool SensorReader::readAllFromSensor()
{
    uint8_t outputBuffer[SENDED_DATA_FRAME_SIZE] = {0U};

    while (true)
    {
        m_pSerialPort->readFromSerial(reinterpret_cast<char*>(&outputBuffer[0U]), SENDED_DATA_FRAME_SIZE);
        parseData(&outputBuffer[0U]);
        usleep(700U);
    }

    return true;
}

bool SensorReader::parseData(uint8_t* data)
{
    // check id we are on beggining of the frame 
    if ( data[0U] == 0x42 && data[1U] == 0x4d )
    [
        
    ]

    return true;
}

uint16_t SensorReader::synthesise(uint8_t HiBit, uint8_t LoBit)
{
    return (HiBit << 8U) + LoBit;
}

