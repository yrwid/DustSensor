// /////////////////////////////////////////////////
// // main.hpp                                    //
// /////////////////////////////////////////////////

#include "CFactory.hpp"

int main(void)
{
	CFactory::getInstance().enableSignal();
	ISerial* port = CFactory::getInstance().getSerialInstance("/dev/ttyUSB0", ISerial::baud9600, 0);
	ISensorReader* dustSensor = CFactory::getInstance().getSensorReaderInstance(port);
	dustSensor->readAllFromSensor();
	//dustSensor->writeToSerial("hello!\n", 7U);
	
	return 0;
}