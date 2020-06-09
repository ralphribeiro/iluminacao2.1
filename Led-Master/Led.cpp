/*
  Led.cpp - Library for flashing Morse code.
  Criado por Ralph Ribeiro, 26 de Maio 2020.
  Classe para agrupar as funcionalidades dos leds.
*/
#include "Arduino.h"
#include "Led.h"

#define RELE 0
#define MOSFET 1

Led::Led(unsigned short int pino, unsigned short int tipo, unsigned short int nivelMin, unsigned short int nivelMax)
{
    pinMode(pino, OUTPUT);
    _pino = pino;
    _tipo = tipo;
    _nivelMin = nivelMin;
    _nivelMax = nivelMax;

    apaga();
}

void Led::acende()
{   
    _nivel = _nivelMax;
    _resetaFade();
    _escrevePorta(_nivel);
}

void Led::apaga()
{   
    if (_tipo == RELE)
        _nivel = HIGH;
    else
    {
        _nivel = 0;
        _resetaFade();
    }
        
    _escrevePorta(_nivel);
}

short int Led::obtemNivel()
{
    return _nivel;
}

bool Led::fade()
{
    return _fade;
}

void Led::ativaFade(bool sentido, unsigned short int degrau, unsigned int intervalo)
{
    _fade = true;
    _sentidoFade = sentido;
    _degrauFade = degrau;
    _intervaloFade = intervalo;
}

bool Led::processaFade()
{
    bool retorno = false;

    if (_fade)
    {
        unsigned long agoraMillis = millis();

        if ((agoraMillis - _ultimoEventoFade) > _intervaloFade)
        {
            if (_sentidoFade)
                incrementaNivel(_degrauFade);
            else
                decrementaNivel(_degrauFade);

            retorno = true;            

            _ultimoEventoFade = agoraMillis;
        }
    }

    return retorno;
}

void Led::incrementaNivel(unsigned short int degrau)
{
    if (_nivel >= _nivelMax - degrau)
    {
        _nivel = _nivelMax;
        _resetaFade();
    }

    if (_nivel < _nivelMax)
        _nivel += degrau;

    _escrevePorta(_nivel);
}

void Led::decrementaNivel(unsigned short int degrau)
{
    if (_nivel <= degrau)
    {
        _nivel = 0;
        _resetaFade();
    }

    if (_nivel > degrau)
        _nivel -= degrau;

    _escrevePorta(_nivel);
}

bool Led::aceso()
{
    if (_tipo == RELE && _nivel == _nivelMax)
        return true;

    if (_tipo == MOSFET && _nivel != 0)
        return true;

    return false;
}

void Led::nivelMinimo()
{
    _nivel = _nivelMin;
    _escrevePorta(_nivel);
}


void Led::_escrevePorta(unsigned short int valor)
{
    if (_tipo == RELE)
        digitalWrite(_pino, valor);
    else if (_tipo == MOSFET)
        analogWrite(_pino, valor);
}

void Led::_resetaFade()
{
    _fade = false;
    _sentidoFade = false;
    _degrauFade = 0;
    _intervaloFade = 0;
    _ultimoEventoFade = 0;
}
