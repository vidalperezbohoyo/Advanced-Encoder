/*
Autor: Vidal Perez Bohoyo.*/

#ifndef AdvancedEncoder_h
#define AdvancedEncoder_h

#include "Arduino.h"

class AdvancedEncoder
{ 
  public:

    AdvancedEncoder(uint8_t pinA, uint8_t pinB);

    // ISRs to call when there is a hw interrupt.
    void ISR_A();
    void ISR_B();

    long getValue(); // Obtain value.

    void setValue(long value); // Set a custom value.
    
    // Set increment or decrement for every encoder tick. Both must be positive numbers.
    void setIncrement(long increment);
    void setDecrement(long decrement);
    
    // Set or remove min/max values that encoder can get. 
    void setRange(long min, long max);  // Min possible: -1073741824  Max possible: 1073741823
    void removeRange();

    bool anyChange(); // Return if there was a change in the encoder value.
    
  private:

    void increase();
    void decrease();

    volatile long value_ = 0;

    int increment_ = 1;
    int decrement_ = 1;

    long range_[] = {-1073741824, 1073741823}; // Min/Max posible

    volatile bool lastA_, lastB_;

    uint8_t pinA_, pinB_;

    bool any_change_ = false;
};

#endif
