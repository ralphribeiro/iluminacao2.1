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
    bool aceso();
    bool fade();
    bool processa();

    short int obtemNivel();
    
    void acende();
    void apaga();
    void ativaFade(bool sentido, unsigned short int degrau, unsigned int intervalo);    
    void ativaTemporizador(unsigned long tempo);
    void decrementaNivel(unsigned short int degrau);
    void incrementaNivel(unsigned short int degrau);
    void manipula();
    void nivelMinimo();
    
    Led(unsigned short int pino, unsigned short int tipo, unsigned short int nivelMin, unsigned short int nivelMax);

private:
    bool _fade;
    bool _sentidoFade;
    
    short int _nivel;
    unsigned short int _pino;
    unsigned short int _tipo;
    unsigned short int _nivelMin;
    unsigned short int _nivelMax;
    unsigned short int _degrauFade;
    unsigned int _intervaloFade;
    
    unsigned long _inicioTemporizador;
    unsigned long _temporizador;
    unsigned long _ultimoEventoFade;
    
    bool _processaFade();
    bool _processaTemporizador();
    
    void _escrevePorta(unsigned short int valor);    
    void _resetaFade();
};

#endif