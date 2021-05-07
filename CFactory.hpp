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
    
    public:
    static CFactory& getInstance();
    ISerial* getSerialInstance();
    ISensorReader* getSensorReaderInstance(ISerial *s);

};

#endif