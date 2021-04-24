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
    uint16_t parsedData[16U] = {0U};
    uint8_t offset = 2U;
    bool retValue = false;

    // check id we are on beggining of the frame 
    if ( data[0U] == 0x42U && data[1U] == 0x4dU )
    {
        // add initial check sum
        uint32_t checkSum = data[0U] + data[1U];

        // parse data
        for (uint8_t iter = 0U; iter < 15U; iter++)
        {
             
            if (iter == 13U || iter == 14U)
            {
                parsedData[iter] = data[2*iter + offset];  // dla 14 zle jest
            }
            else
            {
                parsedData[iter] = synthesise(data[iter*2U + offset], data[iter*2U + offset + 1U]);
            }
        }
        parsedData[15U] = synthesise(data[30U], data[31U]);

        // calculate checksum
        for (uint8_t i = 0U; i < 28U; i++)
        {
            checkSum += data[offset + i];
        } 

        // indicate if parsed data is correct
        retValue = (checkSum == parsedData[15U]) ? true : false;
    }

    return retValue;
}

uint16_t SensorReader::synthesise(uint8_t HiBit, uint8_t LoBit)
{
    return (HiBit << 8U) + LoBit;
}

