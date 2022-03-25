/*
Autor: Vidal Perez Bohoyo.*/

#ifndef AdvancedEncoder_h
#define AdvancedEncoder_h

#include "Arduino.h"


class AdvancedEncoder
{
  public:
    AdvancedEncoder ();

    void ISR_A();
    void ISR_B();

    int obtenerValor();
    void ajustarValor(long valor_esperado);
   
    void ajustarIncremento(int incremento_esperado){ incremento = incremento_esperado; };
    void ajustarDecremento(int decremento_esperado){ decremento = decremento_esperado; };
    
    void ajustarRango(long minimo, long maximo);
    void sinRango(){ existe_rango = false; }; 

    bool algunCambio();
    
  private:

    void aumentarValor();
    void disminuirValor();

    volatile long valor = 0;

    int incremento = 1;
    int decremento = 1;

    long max = 0;
    long min = 0;

    bool existe_rango = false;

    volatile bool lastA;
    volatile bool lastB; 
    bool algun_cambio_ = false;

    
    
};

#endif
