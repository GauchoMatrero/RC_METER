/*
RC METER VERSION 1.1a
Carlos Fedman 04.11.20012
*/
#include <Arduino.h>
#include <LiquidCrystal/LiquidCrystal.h>
#include <math.h>
#include <stdio.h>
#include "R_control.h"
#include "Defines.h"
#include "Globals.h"


float microFarads;                // floating point variable to preserve precision, make calculations
//float nanoFarads;
//byte mode ;    // 0= uF  1 pf
byte Overflow=false;
// LCD RS=8 E=9 DB4=10  DB5=11 DB6=12 DB7=13
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

// Control object
Rcontrol RC (Rcount, DischargePin, Rlist );
// create range object
Range R(Rcount);

void setup()
{
	//  pinMode(DebugPin, OUTPUT);     // Debug Pin
	lcd.begin(8,1);
	RC.FreeAll();  // Ini I/O
	// Make ADC faster by setting AD prescale to 16
	sbi(ADCSRA,ADPS2) ;
	cbi(ADCSRA,ADPS1) ;
	cbi(ADCSRA,ADPS0) ;
	// Print a message to the LCD.
	lcd.print("CMTR 1.1");
	// Calibration Read Open Loop times
	for ( int i=0; i < Rcount ; i++ )
	{
		RC.SetRndx(i);
		RC.EnableR();
		Tmin[i]=readTime(AnalogPin,0);
		RC.FreeR();
	}
	delay(2500);
}
void loop()
{
	int n = 64;
	unsigned long T0;
	unsigned long timestamp[n];
	int  values[n];
	float b,C;
	unsigned long Tdelay;
	unsigned long ElapsedTimeRC;
	unsigned long ElapsedTimeIntrp;
	//float microFaradsRC;
	int i;

	// retrieve actual range
	i=R.get();
	// adjust range R's
	RC.SetRndx(i);
	RC.EnableR();
	ElapsedTimeRC=readTime(AnalogPin,Tmin[i]);
	RC.FreeR();

	if      ( ElapsedTimeRC < 9500 ) R.inc();
	else if ( ElapsedTimeRC > 101000 ) R.dec();
	if ((Overflow==true) && (R.get() != 0))
	{
		lcd.clear();
		lcd.print("OVFL ");
		lcd.print (R.get());
	}

	else
	{
		// Charge C to High level
		Tdelay=ElapsedTimeRC/(unsigned long)n;
		//lcd.clear();
		//lcd.print(ElapsedTimeRC);

		StartIntrpMeasure(RC.GetRpin());
		T0=micros();

		// b) Measure C by exponential Least Min Squares
		//    lcd.clear();
		//    lcd.print(Tdelay);
		digitalWrite(DebugPin, HIGH);
		for (int j=0; j<n; j++)
		{
			timestamp[j]=micros()-T0;
			values[j] = analogRead(AnalogPin);
			if (Tdelay < 1000) delayMicroseconds(Tdelay);
			else delay(Tdelay/(unsigned long)1000);
		}
		digitalWrite(DebugPin, LOW);

		//  Discharge Cap
		RC.FreeR();
		discharge(AnalogPin);
		//After the capacitor discharges below adc resolution
		//all we get are zeros. Toss out the zeroes so they won't
		//skew the results.

		ElapsedTimeIntrp=timestamp[n-1];
		//fit_exp returns 1/b = -RC in us. C = -RC pF.
		b= fit_exp(timestamp,values, n) ;
		//  lcd.clear();
		C= -1/(b *RC.GetRvalue())-((float)Tmin[i]*0.75)*RC.GetRvalue()*1e-12; // normalize to pf
		DisplayC (  C );
	}
	delay ( 500);
}
