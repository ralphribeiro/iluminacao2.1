/*
  Led.h - Library for flashing Morse code.
  Criado por Ralph Ribeiro, 26 de Maio 2020.
  Classe para agrupar as funcionalidades dos leds.
*/
#ifndef Morse_h
#define Morse_h

#include "Arduino.h"

class Led{
public:
    Led(unsigned short int pino, unsigned short int tipo, unsigned short int nivelMin, unsigned short int nivelMax);
    void acende();
    void apaga();
    void incrementaNivel();
    void decrementaNivel();
    bool aceso();
    void nivelMin();

private:
    void _escrevePorta(unsigned short int valor);    
    unsigned short int _pino;
    unsigned short int _tipo;
    unsigned short int _nivel;
    unsigned short int _nivelMin;
    unsigned short int _nivelMax;
};

#endif