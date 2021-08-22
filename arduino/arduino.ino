#include <Led.h>

uint8_t pinBotao1 = 12;
uint8_t pinPSON = 13;
uint8_t pinIR = 4;
uint8_t pinRele1 = A0;
uint8_t pinRele2 = A1;
uint8_t pinRele3 = A2;
uint8_t pinRele4 = A3;
uint8_t pinRele5 = 3;
uint8_t pinMosfet1 = 10;
uint8_t pinMosfet2 = 9;
uint8_t pinMosfet3 = 6;
uint8_t pinMosfet4 = 5;

uint8_t RELE = 0;
uint8_t MOSFET = 1;

uint8_t nivelMin = 5;
uint8_t nivelMax = 240;

unsigned int intervaloEventoFade = 30;
uint8_t degrauFade = 5;

uint8_t ledFundos = 0;
uint8_t ledCorredoFundos = 1;
uint8_t ledCozinha = 2;
uint8_t ledCortesia = 3;
uint8_t ledBico = 4;
Led ledsRele[5] = {
    Led(pinRele1, RELE, HIGH, LOW),
    Led(pinRele2, RELE, HIGH, LOW),
    Led(pinRele3, RELE, HIGH, LOW),
    Led(pinRele4, RELE, HIGH, LOW),
    Led(pinRele5, RELE, LOW, HIGH)};
uint8_t qtdLedsRele = 5;

uint8_t ledSalaUm = 0;
uint8_t ledSalaDois = 1;
uint8_t ledSalaTres = 2;
uint8_t ledSalaQuatro = 3;
Led ledsMosfet[4] = {
    Led(pinMosfet1, MOSFET, nivelMin, nivelMax),
    Led(pinMosfet2, MOSFET, nivelMin, nivelMax),
    Led(pinMosfet3, MOSFET, nivelMin, nivelMax),
    Led(pinMosfet4, MOSFET, nivelMin, nivelMax),
};
uint8_t qtdLedsMosfet = 4;

void setup(){
    iniciaFonte();
    iniciaIR();
    iniciaBotao();
    // iniciaSerial();
}

void loop(){
    gerenciaEventoIR();
    gerenciaBotao();
    gerenciaLed();
    // gerenciaSerial();
}

void desliga(){
    for (uint8_t i = 0; i < qtdLedsRele; i++){
        ledsRele[i].apaga();
    }

    for (uint8_t i = 0; i < qtdLedsMosfet; i++){
        ledsMosfet[i].apaga();
    }

    gerenciaFonte();
}

void gerenciaFonte(){
    algumLedAceso() ? ligaFonte() : desligaFonte();
}

bool algumLedAceso(){
    for (uint8_t i = 0; i < qtdLedsRele; i++){
        if (ledsRele[i].aceso())
            return true;
    }

    for (uint8_t i = 0; i < qtdLedsMosfet; i++){
        if (ledsMosfet[i].aceso())
            return true;
    }

    return false;
}

void manipulaNivelMin(){
    if (ledsMosfet[ledSalaUm].obtemNivel() == nivelMin &&
        ledsMosfet[ledSalaDois].obtemNivel() == nivelMin &&
        ledsMosfet[ledSalaTres].obtemNivel() == nivelMin &&
        ledsMosfet[ledSalaQuatro].obtemNivel() == nivelMin){

        for (uint8_t i = 0; i < qtdLedsMosfet; i++){
            ledsMosfet[i].apaga();
        }
    }
    else{
        for (uint8_t i = 0; i < qtdLedsMosfet; i++){
            ledsMosfet[i].nivelMinimo();
        }
    }
}

void manipulaFade(){
    if (!ledsMosfet[ledSalaUm].fade() &&
        !ledsMosfet[ledSalaDois].fade() &&
        !ledsMosfet[ledSalaTres].fade() &&
        !ledsMosfet[ledSalaQuatro].fade()){

        if (!ledsMosfet[ledSalaUm].aceso() &&
            !ledsMosfet[ledSalaDois].aceso() &&
            !ledsMosfet[ledSalaTres].aceso() &&
            !ledsMosfet[ledSalaQuatro].aceso()){

            for (uint8_t i = 0; i < qtdLedsMosfet; i++){
                ledsMosfet[i].ativaFade(HIGH, degrauFade, intervaloEventoFade);
            }
        }
        else{
            for (uint8_t i = 0; i < qtdLedsMosfet; i++){
                ledsMosfet[i].ativaFade(LOW, degrauFade, intervaloEventoFade);
            }
        }
    }
}

void gerenciaBotao(){
    uint8_t retorno = processaBotao();

    if (retorno > 0){
        switch (retorno){
        case 1:
            ledsRele[ledCortesia].manipula();
            break;

        case 2:
            ledsRele[ledBico].manipula();
            break;

        case 3:
            ledsRele[ledBico].ativaTemporizador(120000);
            break;

        case 5:
            manipulaNivelMin();
            break;

        default:
            break;
        }

        gerenciaFonte();
    }
}

void gerenciaLed(){
    if (ledsMosfet[ledSalaUm].processa() ||
        ledsMosfet[ledSalaDois].processa() ||
        ledsMosfet[ledSalaTres].processa() ||
        ledsMosfet[ledSalaQuatro].processa() ||
        ledsRele[ledBico].processa()){

        gerenciaFonte();
    }
}

void gerenciaSerial(){
    String msg = verificaMensagemSerial();

    if (msg.compareTo("") > 0){
        if (msg == "#LS")
            // ledsRele[ledFundos].aceso() ? ledsRele[ledFundos].apaga() : ledsRele[ledFundos].acende();
            gerenciaFonte();
    }
}

void acendeTodos(){
    for (int i = 0; i < qtdLedsRele; i++){
        ledsRele[i].acende();
    }

    for (int i = 0; i < qtdLedsMosfet; i++){
        ledsMosfet[i].acende();
    }
}

void gerenciaEventoIR(){
    unsigned int comando = irComando();

    if (comando > 0){
        switch (comando){
        case 1:
            desliga();
            break;

        case 2:
            ledsRele[ledFundos].manipula();
            break;

        case 3:
            ledsRele[ledCorredoFundos].manipula();
            break;

        case 4:
            ledsRele[ledCozinha].manipula();
            break;

        case 5:
            ledsMosfet[ledSalaUm].manipula();
            break;

        case 6:
            ledsMosfet[ledSalaDois].manipula();
            break;

        case 7:
            ledsMosfet[ledSalaTres].manipula();
            break;

        case 8:
            ledsMosfet[ledSalaQuatro].manipula();
            break;

        case 9:
            ledsRele[ledBico].manipula();
            break;

        case 10:
            ledsRele[ledCortesia].manipula();
            break;

        case 11:
            if (ledsMosfet[ledSalaTres].aceso())
                ledsMosfet[ledSalaTres].obtemNivel() == nivelMin ? ledsMosfet[ledSalaTres].apaga() : ledsMosfet[ledSalaTres].nivelMinimo();
            else
                ledsMosfet[ledSalaTres].nivelMinimo();
            break;

        case 12:
            manipulaNivelMin();
            break;

        case 14:
            ledsMosfet[ledSalaTres].incrementaNivel(degrauFade);
            break;

        case 15:
            ledsMosfet[ledSalaTres].decrementaNivel(degrauFade);
            break;

        case 16:
            manipulaFade();
            break;

        case 17:
            ledsRele[ledBico].ativaTemporizador(60000);
            break;

        case 18:
            acendeTodos();
            break;

        default:
            break;
        }

        gerenciaFonte();
    }
}
