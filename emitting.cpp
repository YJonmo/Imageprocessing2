#include <QObject>
#include <QString>
#include <stdio.h>
#include "emitting.h"
 
void EmitterTest::setValue(int v)
{
    // if the value has changed
    printf("The new value for %d\n", v);
    mem_value = v;
}
 
void EmitterTest::setValueAndEmit(int v)
{
    // if the value has changed
    if (v != mem_value)
    {
        mem_value = v;
        emit valueChanged(v);
    }
}
 
int main()
{
    EmitterTest em1, em2;
 
    QObject::connect(&em1, SIGNAL(valueChanged(int)),
                     &em2, SLOT(setValue(int)));
 
    em1.setValueAndEmit(10);
    printf("The connection from the object connection em1 %d should equal em2 %d \n", em1.getValue(), em2.getValue());
    em2.setValueAndEmit(15);
    printf("The connection from the object connection em1 %d should NOT equal em2 %d \n", em1.getValue(), em2.getValue());
    // the values are not the same because I have not connected them even though I have called the emit within the
    // setValueAndEmit
    return 0;
}
