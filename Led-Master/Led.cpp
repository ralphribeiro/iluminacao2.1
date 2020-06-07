/*
  Led.cpp - Library for flashing Morse code.
  Criado por Ralph Ribeiro, 26 de Maio 2020.
  Classe para agrupar as funcionalidades dos leds.
*/
#include "Arduino.h"
#include "Led.h"

#define RELE   0
#define MOSFET 1
#define DEGRAU 10

Led::Led(unsigned short int pino, unsigned short int tipo, unsigned short int nivelMin, unsigned short int nivelMax){
    pinMode(pino, OUTPUT);
    _pino = pino;
    _tipo = tipo;
    _nivelMin = nivelMin;
    _nivelMax = nivelMax;

    apaga();    
}

void Led::acende(){
    _nivel = _nivelMax;
    _escrevePorta(_nivelMax);
}

void Led::apaga(){
    _nivel = _nivelMin;
    _escrevePorta(_nivelMin);
}

void Led::incrementaNivel(){
    if(_nivel > _nivelMax - DEGRAU){
        _nivel = _nivelMax;
    }

    if(_nivel < _nivelMax)
        _nivel += DEGRAU;

    _escrevePorta(_nivel);    
}

void Led::decrementaNivel(){
    if(_nivel < DEGRAU){
        _nivel = _nivelMin;
    }

    if(_nivel > DEGRAU)
        _nivel -= DEGRAU;

    _escrevePorta(_nivel);
}

bool Led::aceso(){        
    if(_tipo == RELE && _nivel == _nivelMax)
        return true;
    
    if(_tipo == MOSFET && _nivel != _nivelMin)
        return true;

    return false;
}

void Led::_escrevePorta(unsigned short int valor){
    if(_tipo == RELE)
        digitalWrite(_pino, valor);    
    else if(_tipo == MOSFET)
        analogWrite(_pino, valor);    
}