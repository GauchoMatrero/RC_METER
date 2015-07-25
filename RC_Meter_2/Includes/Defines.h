#ifndef DEFINES_
#define DEFINES_
//extern Rcontrol RC (int n, int rstpin,   _R p[] ); /*  PIN ASIGNATION
/*
 D13  out Db7 LCD (9)
 D12  out DB6 LCD (8)
 D11  out DB5 LCD (7)
 D10  out DB4 LCD (6)
 D9   out E   LCD (5)
 D8   out R/S LD  (2)

 D7  in/out  2k2 Discharge
 D6  in/out R4 1MEG
 D5  in/out R3 100K
 D4  in/out R2 10K
 D3  in/out R1 1K
 D2  IN Cal BTN
 D1  debug

 A0  inp ON  Sw
 A1
 A2
 A3
 A4
 A5
 */
// Pinout

#define AnalogPin      A0          // analog pin for measuring capacitor voltage
#define CalibratePin   2
#define DischargePin   7          // pin to discharge the capacitor
#define LedPin         1
#define DebugPin       0
// R Network
#define Rcount    4
#define PinR1     3
#define PinR2     4
#define PinR3     5
#define PinR4     6
#define R1       1.005e3F
#define R2       9.98e3F
#define R3       100.4e3F
#define R4       1.011e6F
// Calibration
#define TMIN 6   /* min time in us */
// Control object
//Rcontrol RC (Rcount, DischargePin, Rlist );
// create range object
//Range R(Rcount);

// defines for setting and clearing register bits
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

// some needed prototypes for Codeblocks
unsigned long  readTime(int AnalogPin, unsigned Tmin);
void discharge(int AnlgPin);
void DisplayC ( float microFarads );
float fit_exp(unsigned long *xs, int *ys,  int n );
void StartIntrpMeasure(int _ndx);
#endif
