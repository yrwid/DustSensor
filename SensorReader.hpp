#ifndef SENSOR_READER_H
#define SENSOR_READER_H

#include "ISerial.hpp"
#include "ISensorReader.hpp"
#include <stdint.h>

class SensorReader : public ISensorReader
{
private:
    // private fields
    ISerial* m_pSerialPort;
    const uint8_t SENDED_DATA_FRAME_SIZE = 32U;
    uint16_t m_parsedData[16U];

    // private methods
    bool parseData(uint8_t* data);
    inline uint16_t synthesise(uint8_t HiBit, uint8_t LoBit);
    void displayData(bool isDataGoo);

public:
    SensorReader(ISerial*);
    ~SensorReader();
    virtual bool readAllFromSensor() override;
};

#endif