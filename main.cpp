// /////////////////////////////////////////////////
// // main.hpp                                    //
// /////////////////////////////////////////////////

#include <unistd.h>
#include "CGetter.hpp"

int main(void)
{
	// char portname[] = { "/dev/ttyUSB0" };
	// Serial dustSensor(portname);

	// dustSensor.setInterfaceAttribs(Serial::baud115200, 0); // set speed to 115,200 bps, 8n1 (no parity) 

	// dustSensor.writeToSerial("hello!\n", 7U);
	// usleep ((7 + 25) * 100);             		// sleep enough to transmit the 7 plus
	// 									 		// receive 25:  approx 100 uS per char transmit
	// char buf [100];
	// dustSensor.readFromSerial(&buf[0U], 7U);
	// return 0;

	CGetter::getInstance();

	return 0;
}