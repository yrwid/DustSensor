// /////////////////////////////////////////////////
// // main.hpp                                    //
// /////////////////////////////////////////////////

#include "CFactory.hpp"
#include "unistd.h"

int main(void)
{
	CFactory::getInstance().enableSignal();
	ISerial* port = CFactory::getInstance().getSerialInstance("/dev/ttyUSB0", ISerial::baud9600, 0);
	ISensorReader* dustSensor = CFactory::getInstance().getSensorReaderInstance(port);
	while(true)
	{
		dustSensor->readSingleFromSensor();
		usleep(700000); 
	}

	//dustSensor->readAllFromSensor();
	
	return 0;
}