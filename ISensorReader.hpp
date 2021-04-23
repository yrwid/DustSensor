#ifndef I_SENSOR_READER_H
#define I_SENSOR_READER_H

class ISensorReader
{
    public:
        virtual bool readAllFromSensor() = 0;
};
#endif