#include "Arduino.h"
#include "AdvancedEncoder.h"

AdvancedEncoder::AdvancedEncoder(uint8_t pinA, uint8_t pinB) {
    pinA_ = pinA;
    pinB_ = pinB;
    // Set a initial last state
    lastA_ = digitalRead(pinA_);
    lastB_ = digitalRead(pinB_);
}

void AdvancedEncoder :: ISR_A()
{
    delayMicroseconds(500); // Small debounce Upgade better
    bool actualA = digitalRead(2);
    bool actualB = digitalRead(3);

    // 00
    if (actualA ==  LOW && actualB == LOW)  
    {
        if (lastA == true && lastB == false) // Last (10)
        {
            aumentarValor();
        }
    }
    
    // 01
    else if (actualA ==  LOW && actualB == HIGH)  
    {
        if (lastA == true  && lastB == true) // Last (11)
        {
            disminuirValor();
        }
    }
    // 10
    else if (actualA ==  HIGH && actualB == LOW)  
    {
        if (lastA == false  && lastB == false) // Last (00)
        {
            disminuirValor();
        }
    }
    // 11
    else
    {
        if (lastA == false && lastB == true) // Last (01)
        {
            aumentarValor();
        }
    }

    lastA = actualA;
    lastB = actualB;
    
    }

void AdvancedEncoder::ISR_B()
{
    delayMicroseconds(500);
    bool actualA = digitalRead(2);
    bool actualB = digitalRead(3);

    // 00
    if (actualA ==  LOW && actualB == LOW)  
    {
        if (lastA == false  && lastB == true) // Last (01)
        {
            disminuirValor();
        }
    }
    
    // 01
    else if (actualA ==  LOW && actualB == HIGH)  
    {
        if (lastA == false && lastB == false) // Last (00)
        {
            aumentarValor();
        }
    }
    // 10
    else if (actualA ==  HIGH && actualB == LOW)  
    {
        if (lastA == true && lastB == true) // Last (11)
        {
            aumentarValor();
        }
    }
    // 11
    else
    {
        if (lastA == true  && lastB == false) // Last (10)
        {
            disminuirValor();
        }
    }

    lastA = actualA;
    lastB = actualB;
}

int AdvancedEncoder::obtenerValor()
{
    return valor/2;
}

void AdvancedEncoder::ajustarValor(long valor_esperado)
{
    valor = valor_esperado * 2;
}

void AdvancedEncoder::ajustarRango(long minimo_esperado, long  maximo_esperado)
{
    min = minimo_esperado * 2;
    max = maximo_esperado * 2;
    existe_rango = true; 
}

// Private 
void AdvancedEncoder::aumentarValor()
{
    if ( !existe_rango || valor + incremento <= max )
    { 
        valor += incremento;
    }
    algun_cambio_ = true;
}

void AdvancedEncoder::disminuirValor()
{
    if ( !existe_rango || valor - decremento >= min )
    { 
        valor -= decremento;
    }
    algun_cambio_ = true;
}

bool AdvancedEncoder::algunCambio()
{
    if (algun_cambio_)
    {
        algun_cambio_ = false;
        return true;
    }else
        return false;
}