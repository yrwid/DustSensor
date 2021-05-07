// /////////////////////////////////////////////////
// // main.hpp                                    //
// /////////////////////////////////////////////////

#include <unistd.h>
#include "CFactory.hpp"
#include <iostream>
#include <signal.h>

void my_handler(int s){
           printf("Caught signal %d\n",s);
           exit(1); 

}

void initSignals()
{
	struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = my_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);
}

void configurePorts(ISerial* port)
{
	port->setUsbDev("/dev/ttyUSB0");
	port->setInterfaceAttribs(ISerial::baud9600, 0);
}

int main(void)
{
	initSignals();
	ISerial* port = CFactory::getInstance().getSerialInstance();
	configurePorts(port);

	ISensorReader* dustSensor = CFactory::getInstance().getSensorReaderInstance(port);
	dustSensor->readAllFromSensor();
	//dustSensor->writeToSerial("hello!\n", 7U);
	
	return 0;
}