#ifndef CFACTORY_H
#define CFACTORY_H

#include "ISerial.hpp"
#include "ISensorReader.hpp"

class CFactory
{
    private:
    // Private Constructor
    CFactory();
    // Stop the compiler generating methods of copy the object
    CFactory(CFactory const& copy);            // Not Implemented
    CFactory& operator=(CFactory const& copy); // Not Implemented
    void* signalObj;
    
    public:
    static CFactory& getInstance();
    ISerial* getSerialInstance(const char* devName, const int baud, int isBlocking);
    ISensorReader* getSensorReaderInstance(ISerial *s);
    void enableSignal();

};

#endif