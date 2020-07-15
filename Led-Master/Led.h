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
    void incrementaNivel(unsigned short int degrau);
    void decrementaNivel(unsigned short int degrau);
    bool aceso();
    void nivelMinimo();
    short int obtemNivel();
    bool fade();
    void ativaFade(bool sentido, unsigned short int degrau, unsigned int intervalo);    
    void ativaTemporizador(unsigned long tempo);
    bool processa();

private:
    void _escrevePorta(unsigned short int valor);    
    unsigned short int _pino;
    unsigned short int _tipo;
    short int _nivel;
    unsigned short int _nivelMin;
    unsigned short int _nivelMax;
    bool _fade;
    bool _sentidoFade;
    unsigned long _ultimoEventoFade;
    unsigned int _intervaloFade;
    unsigned short int _degrauFade;
    void _resetaFade();
    bool _processaFade();
    bool _processaTemporizador();
    unsigned long _temporizador;
    unsigned long _inicioTemporizador;
};

#endif