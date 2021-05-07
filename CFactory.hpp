#ifndef CGETTER_H
#define CGETTER_H

#include "ISerial.hpp"
#include "ISensorReader.hpp"

class CGetter
{
    private:
    // Private Constructor
    CGetter();
    // Stop the compiler generating methods of copy the object
    CGetter(CGetter const& copy);            // Not Implemented
    CGetter& operator=(CGetter const& copy); // Not Implemented
    
    public:
    static CGetter& getInstance();
    ISerial* getSerialInstance();
    ISensorReader* getSensorReaderInstance(ISerial *s);

};

#endif