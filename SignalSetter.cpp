#include "SignalSetter.hpp"
#include <signal.h>
#include <iostream>

void signalHandler(int s){
           printf("Caught signal %d\n",s);
           exit(1); 

}

SignalSetter::SignalSetter()
{
    initSignals();
}

SignalSetter::~SignalSetter()
{
}

void SignalSetter::initSignals()
{
	struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = signalHandler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);
}