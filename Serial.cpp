// /////////////////////////////////////////////////
// // serial.cpp                 				  //
// /////////////////////////////////////////////////

#include <stdio.h> 
#include <errno.h>
#include <fcntl.h> 
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <iostream>
#include "Serial.hpp"
#include "ISerial.hpp"

Serial::Serial()
{
	//setUsbDev("test");
}

Serial::~Serial()
{
	close(m_FD);
}

bool Serial::setUsbDev(const char * const portName)
{
	m_pPortName = portName;
	// check if fd is alredy assigned const value ??
	m_FD = open(portName, O_RDWR | O_NOCTTY | O_SYNC );

	if (m_FD < 0)
	{
		printf("error %d opening %s: %s", errno, portName, strerror(errno));
	}

	return true;
}

void Serial::flushPortBuffer()
{
	int nread;
	while(nread > 0)
	{
		ioctl(m_FD, FIONREAD, &nread);
		uint8_t* matrix = new uint8_t[nread];
		read(m_FD, matrix, nread);
		delete[] matrix;
	}

	ioctl(m_FD, FIONREAD, &nread);

	if (nread != 0)
	{
		std::cout << "Port is not empty" << std::endl;
	}
}

int Serial::setInterfaceAttribs (int speed, int parity)
{
	struct termios tty;

	if (tcgetattr(m_FD, &tty) != 0)
	{
		printf("error %d from tcgetattr, filedestriptor %d \n", errno, m_FD);
		return -1;
	}

	cfsetospeed(&tty, speed);
	cfsetispeed(&tty, speed);

	tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
													// disable IGNBRK for mismatched speed tests; 
													// otherwise receive break as \000 chars
	tty.c_iflag &= ~IGNBRK;         // disable break processing
	tty.c_lflag = 0;                // no signaling chars, no echo,
									// no canonical processing
	tty.c_oflag = 0;                // no remapping, no delays
	tty.c_cc[VMIN]  = 0;            // read doesn't block
	tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

	tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

	tty.c_cflag |= (CLOCAL | CREAD);		// ignore modem controls,
											// enable reading
	tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
	tty.c_cflag |= parity;
	tty.c_cflag &= ~CSTOPB;
	tty.c_cflag &= ~CRTSCTS;

	if (tcsetattr (m_FD, TCSANOW, &tty) != 0)
	{
		printf("error %d from tcsetattr", errno);
		return -1;
	}

	setBlocking(0);        // set no blocking

	return 0;
}

void Serial::setBlocking (int should_block)
{
	struct termios tty;
	memset (&tty, 0, sizeof tty);

	if (tcgetattr (m_FD, &tty) != 0)
	{
		printf("error %d from tggetattr", errno);
		return;
	}

	tty.c_cc[VMIN]  = should_block ? 1 : 0;
	tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

	if (tcsetattr(m_FD, TCSANOW, &tty) != 0)
	{
		printf("error %d setting term attributes", errno);
	}
}

int Serial::writeToSerial(const char* message, size_t len)
{
	return write(m_FD, message, len);
}

// int nread;
// ioctl(Serial, FIONREAD, &nread);
int Serial::readFromSerial(char* output, size_t len)
{
	int nread;
	ioctl(m_FD, FIONREAD, &nread);
	if (nread >= len)
	{
		return read(m_FD, output, len);
	}

  return -1;
}