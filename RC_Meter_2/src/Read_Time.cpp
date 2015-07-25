#line 1

#include <Arduino.h>
#include "defines.h"
#include "R_control.h"

extern Rcontrol RC ;
extern byte Overflow;

unsigned long  readTime(int AnalogPin, unsigned Tmin)
{
    unsigned long startTime,endTime;
    unsigned long _elapsedTime;
    unsigned long MaxTime;
    //  unsigned long Tmin;
    static byte ping =false;
//Maximal RC allowed
    if (RC.GetRndx () == 0)    MaxTime = 5000000;  // 5 seconds for biggest range
    else                 MaxTime = 500000;         // half a second for others
//MaxTime = 500000;
    /* discharge the capacitor  */
    discharge(AnalogPin);
    RC.SetVal(HIGH);
    startTime = micros();
    Overflow=false;
    /*wait to 62% of Vref */
    while(analogRead(AnalogPin) < 648)
    {
        if ((micros()-startTime)> MaxTime)
        {
            Overflow=true;
            break;
        }
    }       // 647 is 63.2% of 1023, which corresponds to full-scale voltage
    endTime= micros();
    /* Compute time */
    _elapsedTime= endTime - startTime;
    /****** CALIBRATION *********/
    return ((_elapsedTime < Tmin) ? 0 : _elapsedTime - Tmin) ;
}

void discharge(int AnlgPin)
{
    RC.EnableRst();
    RC.SetValRst(LOW);
    while(analogRead(AnlgPin) > 10);         // wait until capacitor is completely discharged
    delay(500); //
    RC.FreeRst();
}
























