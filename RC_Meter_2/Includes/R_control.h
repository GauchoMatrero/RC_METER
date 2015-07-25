#ifndef R_CONTROL_H
#define R_CONTROL_H


struct _R
{
    int pin;
    float value;
};

class Rcontrol
{
public:
    int SetRndx  (int i);      // Selects R
    int GetRndx ();            // Retrieves active R index
    int GetRpin();             // Retrieves active R pin
    float GetRvalue();         // Retrieves active R value
    void FreeAll();            // disables all Rs & ResetR
    void EnableR();            // Enable activeR
    void EnableRst();          // Enable RST
    void FreeR();              // Disable activeR
    void FreeRst();            // Disable RST
    void SetVal (int value);    // Enable & write a level to Active R
    void SetValRst (int value); // Writes a level to RST

    Rcontrol (int n, int rstpin, _R p[] );
private:
    int _n;            // number of Rs
    int _R_actual;     // Active pin #0
    int _RstPin;       // Reset pin
    _R*  _p ;          // list of pin # and values
};

class Range
{
    int _i;  // actual range
    int _min; // min range
    int _max; // max range;
public:
    Range (int maxv);
    Range (int minv, int maxv);
    void inc();
    void dec();
    void set(int v);
    void rst();
    int get();
};

//#endif
#endif // R_CONTROL_H
