#ifndef SIGNAL_SETTER_HPP
#define SIGNAL_SETTER_HPP

class SignalSetter
{
private:
public:
    SignalSetter();
    ~SignalSetter();
    void attacheInterruptSignal();
    void initSignals();
};

#endif