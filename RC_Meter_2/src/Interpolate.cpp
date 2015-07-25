#line 1

#include <Arduino.h>

float fit_exp(unsigned long *xs, int *ys,  int n )
{
    float sumy = 0;
    float sumxy = 0;
    float sumxxy = 0;
    float sumxylny=0;
    float sumylny=0;
    //  float sumx=0;
    //  float sumlny=0;
    //  float sumxlny=0;
    //  float sumxx=0;
    float xy;
    float lny ;
    float fx,fy,fxxy;

    float a,b;
    //  float a_1,b_1;
    unsigned long T=0;
    float yy0,lnyy0;
    float C;
    unsigned long Cmean=0;
    int i;
    unsigned long x,y;
//  Serial.println();
    for(i=0; i<n; i++)
    {
        x = xs[i];
        y = ys[i];
        xy = x*y;
        lny = log(y);
        sumy+= y;
        sumxy += xy;
        fx=x;
        fy=y;
        sumxxy +=  fx*fx*fy;
        sumxylny += xy*lny;
        sumylny += y*lny;
        // Calculate C
        T=x;
        yy0=(float)ys[i]/(float)ys[0];
        lnyy0=log(yy0);
        C=-(float)(T*10)/lnyy0;
        Cmean=Cmean+C;
    }
    b= (sumy*sumxylny-sumxy*sumylny) / (sumy*sumxxy-sumxy*sumxy);
    Cmean=Cmean/(n-1);
    b= (sumy*sumxylny-sumxy*sumylny) / (sumy*sumxxy-sumxy*sumxy);
    return (b);
}



