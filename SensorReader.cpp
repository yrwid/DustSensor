#include "SensorReader.hpp"
#include <unistd.h>
#include <iostream>

SensorReader::SensorReader( ISerial* pSerial ) : 
    m_pSerialPort( pSerial ),
    m_passiveMode(false)
{
}

bool SensorReader::readAllFromSensor()
{
    uint8_t outputBuffer[SENDED_DATA_FRAME_SIZE] = {0U};
    uint8_t flushCounter = 0U;
    
    std::cout<<"before petla"<<std::endl;
    do
    {
        const bool result = (m_pSerialPort->readFromSerial(reinterpret_cast<char*>(&outputBuffer[0U]), SENDED_DATA_FRAME_SIZE) > 0); 
                            
        if (result)
		{
            std::cout<<"w IFie"<<std::endl;
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

        //m_pSerialPort->flushPortBuffer();

        usleep(500000); // 700ms 
    } while (!m_passiveMode);

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

bool SensorReader::readSingleFromSensor()
{
    // last 2 bytes are sum of previous ones. 
    const uint8_t chngeToPassiveMode[]  = {0x42, 0x4d, 0xe1, 0x00, 0x00, 0x01, 0x70 }; // Passive
    const uint8_t chngeToActiveMode[]   = {0x42, 0x4d, 0xe1, 0x00, 0x01, 0x01, 0x71 }; // Active
    const uint8_t readFromPassiveMode[] = {0x42, 0x4d, 0xe2, 0x00, 0x00, 0x01, 0x71 }; // Read from passive mode
    const uint8_t enableSleepMode[]     = {0x42, 0x4d, 0xe4, 0x00, 0x00, 0x01, 0x73 }; // Sleep mode
    const uint8_t wakeupFromSleepMode[] = {0x42, 0x4d, 0xe4, 0x00, 0x01, 0x01, 0x74 }; // wake up from sleep mode

    int resultOfSend = 0;

    if(!m_passiveMode)
    {
        usleep(100000); // 100ms 
        resultOfSend = m_pSerialPort->writeToSerial(reinterpret_cast<const char*>(chngeToPassiveMode), 
                                                    sizeof(chngeToPassiveMode)/sizeof(chngeToPassiveMode[0U]));

        std::cout<<"value of send: "<< resultOfSend<<std::endl;
        if (resultOfSend < 0)
        {
            return false;
        }
    }

    m_passiveMode = true;
    usleep(700000); // 100ms 
    m_pSerialPort->flushPortBuffer();

    resultOfSend = m_pSerialPort->writeToSerial(reinterpret_cast<const char*>(readFromPassiveMode), 
                                                sizeof(readFromPassiveMode)/sizeof(readFromPassiveMode[0U]));

    if (resultOfSend < 0)
    {
        return false;
    }

    usleep(10000); // 100ms 
    return readAllFromSensor();
}