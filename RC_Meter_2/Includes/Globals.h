#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

#include "R_control.h"
// Resistor & pin list
_R Rlist[Rcount] =
{
    {
        PinR1,R1
    }
    ,{
        PinR2,R2
    }
    ,{
        PinR3,R3
    }
    ,{
        PinR4,R4
    }
}
;
// Minimal Time Measuremen
unsigned Tmin[Rcount] =
{
    0,0,0,0
};


#endif // GLOBALS_H_INCLUDED
