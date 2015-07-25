#line 1

#include <Arduino.h>
#include <LiquidCrystal.h>

void DisplayC ( float microFarads );
void lcdShow (float v, int units );
extern LiquidCrystal lcd;

/**** READ BY RC TIME CONSTANT */


void DisplayC ( float microFarads )
{
    if      (microFarads > 1000.0)   lcdShow (microFarads*1E-3,0); //mf
    else if (microFarads > 1.0)      lcdShow (microFarads,1); //uf
    else if ( microFarads > .001 )   lcdShow( microFarads*1.0E3,2); //nf
    else                             lcdShow( microFarads*1.0E6, 3); // pf
}

void lcdShow (float v, int units )
{
    int ival,ip,dp;
    lcd.clear() ;
    v=abs(v);
    ip= (int long)v;
    lcd.print (ip);
    lcd.print (".");

    if (v<10)  // three decimals
    {
        ival= (int long )(v*1000);
        dp= ival %1000;
        if (dp > 99 )   lcd.print (dp);
        else if (dp > 9 )
        {
            lcd.print ("0");
            lcd.print (dp);
        }
        else
        {
            lcd.print ("00");
            lcd.print (dp);
        }

    }
    else if (v<100) // two decimals
    {
        ival= (int long)(v*100);
        dp= ival %100;
        if (dp > 9 )   lcd.print (dp);
        else
        {
            lcd.print ("0");
            lcd.print (dp);
        }
    }
    else  // one decimal
    {
        ival= (int long)(v*10);
        dp= ival %10;
        lcd.print (dp);

    }


    switch ( units )
    {
    case 0:
        lcd.print (" mF");
    case 1:
        lcd.print (" uF");
    case 2:
        lcd.print (" nF");
    default:
        lcd.print (" pF");
    }
}










