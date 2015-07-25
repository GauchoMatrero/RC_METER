#line 1
#include "R_control.h"
#include <Arduino.h>

Rcontrol::Rcontrol (int n, int rstpin, _R p[] )
{
//    int i;
    _n=n;            // number of Rs
    _R_actual=0;      // Active pin #0
    _RstPin=rstpin;  // Reset pin
    _p=p;            // list of pin # and values
    pinMode(_RstPin, INPUT);     // set ResetPin to output
    digitalWrite(_RstPin,LOW);
    Rcontrol::FreeAll();
}
// Selects R
int Rcontrol::SetRndx(int i)
{
    if (i <0 || i >_n) return -1 ;    // Error  n not in range
    _R_actual=i;   // Store actual pointer to R
    return i;      // Signal happy end
}
// Retrieves active R
int Rcontrol::GetRndx()
{
    return _R_actual ;
}
// Retrieves active R pin
int Rcontrol::GetRpin()
{
    return (_p[_R_actual].pin);
}
// Retrieves active R value
float Rcontrol::GetRvalue()
{
    return _p[_R_actual].value;
}

// disables all Rs & ResetR
void Rcontrol::FreeAll()
{
    // Define Initial State
    for ( int i=0; i <_n; i++ )
    {
        pinMode(_p[i].pin, INPUT);   // Config Ri as Input
        digitalWrite(_p[i].pin, LOW); // Disable Pullup
    }
}
// Enable activeR
void  Rcontrol::EnableR()
{
    pinMode(_p[_R_actual].pin, OUTPUT);   // Config Ri as Input
}
// Enable RST
void  Rcontrol::EnableRst()
{
    pinMode(_RstPin, OUTPUT);   // Config Ri as Input
}

// Disable activeR
void  Rcontrol::FreeR()
{
    pinMode(_p[_R_actual].pin, INPUT);   // Config Ri as Input
    digitalWrite(_p[_R_actual].pin, LOW); // Disable Pullup
}
// Disable RST
void Rcontrol::FreeRst()
{
    pinMode(_RstPin, INPUT);   // Config Ri as Input
    digitalWrite(_RstPin, LOW); // Disable Pullup
}
// Enable & write a level to Active R
void Rcontrol::SetVal (int value)
{
//  digitalWrite(DebugPin, HIGH);
    digitalWrite(_p[_R_actual].pin, value); // Write Value
//  digitalWrite(DebugPin, LOW);

}
// Writes a level to RST
void Rcontrol::SetValRst (int value)
{
    pinMode(_RstPin, OUTPUT);   // Config Rst  as Output
    digitalWrite(_RstPin, value); // Write Value
}

// Range control
Range::Range (int minv, int maxv)
{
    _min=minv; // min range
    _max=maxv; // max range;
    _i=_min;
}
Range::Range ( int maxv)
{
    _min=0   ; // min range
    _max=maxv; // max range;
    _i=_min;
}
// Increment range, test if off limits
void Range::inc()
{
    int i = _i+1;
    if ((i>=_min) && (i<_max)) _i=i;
}
// Decrement range, test if off limits
void Range::dec()
{
    int i = _i-1;
    if ((i>=_min) && (i<_max)) _i=i;
}
// Set range, test if off limits
void Range::set(int v)
{
    if ((v>=_min) && (v<_max)) _i=v;
}
// Zero range, test if off limits
void Range::rst()
{
    _i=_min; // min range
}
// Get range value
int Range::get()
{
    return _i;
}







