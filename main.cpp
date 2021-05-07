// /////////////////////////////////////////////////
// // main.hpp                                    //
// /////////////////////////////////////////////////

#include <unistd.h>
#include "CGetter.hpp"
#include <iostream>
#include <signal.h>

void my_handler(int s){
           printf("Caught signal %d\n",s);
           exit(1); 

}

int main(void)
{
	// break signal - fnct
	struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = my_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);
	// end

	ISerial* port = CGetter::getInstance().getSerialInstance();

	// configure port - fnct
	port->setUsbDev("/dev/ttyUSB0");
	port->setInterfaceAttribs(ISerial::baud9600, 0);
	// end

	ISensorReader* dustSensor = CGetter::getInstance().getSensorReaderInstance(port);
	dustSensor->readAllFromSensor();
	//dustSensor->writeToSerial("hello!\n", 7U);
	
	return 0;
}