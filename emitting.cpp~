#ifndef EMITTING_H
#define EMITTING_H
 
#include <QObject>
 
class EmitterTest : public QObject
{
    Q_OBJECT
 
    public:
        EmitterTest() { mem_value = 0;}
 
        int getValue() const { return mem_value;}
        void setValueAndEmit(int v);
 
    // these pick up the emitted signal
    public slots :
        void setValue(int v);
 
    // these are what are sent out over emitted signals
    // you do not implement the signals since they are just virtual functions
    // as such that you call with emit then the value within the parameter(s)
    // is passed to the slot.
    signals:
        void valueChanged(int newV);
 
    private:
        int mem_value;
};
 
#endif // EMITTING_H
