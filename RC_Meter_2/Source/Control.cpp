#line 1
#include <Arduino.h>
#include "Defines.h"#include "R_control.h"
extern Rcontrol RC ;

void StartIntrpMeasure(int _ndx){
  //  RC.SetRndx(_ndx); // Discharge pin used
  //  RC.FreeAll(); // all pullups as
  RC.SetVal(HIGH); // on pullup r
  RC.EnableRst();   // on reset
  RC.SetValRst(HIGH); // Charges C
  while(analogRead(AnalogPin) < 900)  ; //wait for the capacitor to charge
  RC.FreeRst(); // stops charging
  RC.EnableR();
  RC.SetVal (LOW); // begins discharging with Selected R
}



