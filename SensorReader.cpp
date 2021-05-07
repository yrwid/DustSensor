#include "SensorReader.hpp"
#include <unistd.h>
#include <iostream>

SensorReader::SensorReader( ISerial* pSerial ) : m_pSerialPort( pSerial )
{    
}

bool SensorReader::readAllFromSensor()
{
    uint8_t outputBuffer[SENDED_DATA_FRAME_SIZE] = {0U};
    uint8_t flushCounter = 0U;

    m_pSerialPort->flushPortBuffer();

    while (true)
    {
        const bool result = (m_pSerialPort->readFromSerial(reinterpret_cast<char*>(&outputBuffer[0U]), SENDED_DATA_FRAME_SIZE) > 0) 
                            ? true : false;
        if (result)
		{
			for (uint8_t i = 0; i < SENDED_DATA_FRAME_SIZE; i++)
			{
				printf("%d ", outputBuffer[i]);
			}
			std::cout << "\n";

            const bool isDataGood = parseData(&outputBuffer[0U]);
            for (uint8_t i = 0; i < SENDED_DATA_FRAME_SIZE/2U; i++)
			{
				printf("%d ", m_parsedData[i]);
			}
			std::cout << "\n";
            displayData(isDataGood);
		}
        else
        {
            flushCounter++;
        }

        if (flushCounter >= 20U)
        {
            flushCounter = 0U;
            m_pSerialPort->flushPortBuffer();
        }

        usleep(100000); // 100ms 
    }

    return true;
}

bool SensorReader::parseData(uint8_t* data)
{
    const uint8_t offset = 2U;
    bool retValue = false;
    const uint8_t frameBegining[] = {0x42U, 0x4dU};
    const uint8_t checkSumLength = 28U;

    // check id we are on beggining of the frame 
    if ( data[0U] == frameBegining[0U] && data[1U] == frameBegining[1U])
    {
        // add initial check sum
        uint32_t checkSum = data[0U] + data[1U];

        // parse data
        for (uint8_t iter = 0U; iter < 16U; iter++)
        {
            if (iter == 13U)
            {
                m_parsedData[iter] = data[28U];
            }
            else if (iter == 14U)
            {
                m_parsedData[iter] = data[29U];
            }
            else if (iter == 15U)
            {
                m_parsedData[iter] = synthesise(data[30U], data[31U]);
            }
            else
            {
                m_parsedData[iter] = synthesise(data[iter*2U + offset], data[iter*2U + offset + 1U]);
            }
        }

        // calculate checksum
        for (uint8_t i = 0U; i < checkSumLength; i++)
        {
            checkSum += data[offset + i];
        } 

        // indicate if parsed data is correct
        retValue = (checkSum == m_parsedData[15U]) ? true : false;
    }

    return retValue;
}

inline uint16_t SensorReader::synthesise(uint8_t HiBit, uint8_t LoBit)
{
    return (HiBit << 8U) + LoBit;
}

void SensorReader::displayData(bool isDataGood)
{
    const char* const displayMatrix[16U] = 
        {
            "Frame length: ",
            "Concentration PM1_0_CF1: ",
            "Concentration PM2_5_CF1: ",
            "Concentration PM10_0_CF1: ",
            "Concentration PM1_0_ATM: ",
            "Concentration PM2_5_ATM: ",
            "Concentration PM10_0_ATM: ",
            "RawGt0_3um: ",
            "RawGt0_5um: ",
            "RawGt1_0um: ",
            "RawGt2_5um: ",
            "RawGt5_0um: ",
            "RawGt10_0um: ",
            "Version: ",
            "Error code: ",
            "Payload checksum: "
        };

    if (isDataGood)
    {
        std::cout << "#################################" << std::endl;
        for (int i = 0U; i < SENDED_DATA_FRAME_SIZE/2U; i++)
        {
           std::cout << displayMatrix[i] << m_parsedData[i] << std::endl;
        }
        std::cout << "################################# \n\n" << std::endl;
    }
    else
    {
        std::cout << "Bad data payload" << std::endl;
    }
}
