#include <IRremote.h>

#define IrPower 0x20DF10EF
#define IrTv 0x20DFF00F
#define IrCaption 0x20DF9C63
#define IrSleep 0x20DF708F
#define IrRatio 0x20DF9E61
#define IrInput 0x20DFD02F
#define Ir1 0x20DF8877
#define Ir2 0x20DF48B7
#define Ir3 0x20DFC837
#define Ir4 0x20DF28D7
#define Ir5 0x20DFA857
#define Ir6 0x20DF6897
#define Ir7 0x20DFE817
#define Ir8 0x20DF18E7
#define Ir9 0x20DF9867
#define Ir0 0x20DF08F7
#define IrList 0x20DF32CD
#define IrQview 0x20DF58A7
#define IrVolmais 0x20DF40BF
#define IrVolmenos 0x20DFC03F
#define IrFav 0x20DF7887
#define IrGuide 0x20DFD52A
#define IrMute 0x20DF906F
#define IrChmais 0x20DF00FF
#define IrChmenos 0x20DF807F
#define IrPicture 0x20DFB24D
#define IrInfo 0x20DF55AA
#define IrSound 0x20DF4AB5
#define IrSettings 0x20DFC23D
#define IrQmenu 0x20DFA25D
#define IrCima 0x20DF02FD
#define IrBaixo 0x20DF827D
#define IrEsquerda 0x20DFE01F
#define IrDireita 0x20DF609F
#define IrOk 0x20DF22DD
#define IrBack 0x20DF14EB
#define IrExit 0x20DFDA25
#define IrBola 0x20DFDD22
#define IrRec 0x20DFBD42
#define IrStop 0x20DF8D72
#define IrReward 0x20DFF10E
#define IrPlay 0x20DF0DF2
#define IrPause 0x20DF5DA2
#define IrFoward 0x20DF718E
#define IrVermelho 0x20DF4EB1
#define IrVerde 0x20DF8E71
#define IrAmarelo 0x20DFC639
#define IrAzul 0x20DF8679

#define AlexaCozinha 0xFFC03F
#define AlexaSofa 0xFF20DF
#define AlexaPorta 0xFFA05F
#define AlexaDispensa 0xFF40BF
#define AlexaFundos 0xFF807F
#define AlexaPortaEntrada 0xFF00FF
#define AlexaGaragem 0xFF906F
#define AlexaSalaQuatro 0xFFE01F
#define AlexaSalaTres 0xFF609F
#define AlexaAcendeTudo 0xFFB04F
#define AlexaApagaTudo 0xFF50AF
#define AlexaModoNoturno 0xFFB847
#define AlexaLampiao 0xFFC23D

unsigned long ultimaLeitura = 0;
unsigned long leituraDelay = 100;

extern uint8_t pinIR;

IRrecv irrecv(pinIR);
decode_results resultados;

long lerIR()
{
    long valor = 0;
    unsigned long agora = millis();
 
    if ((agora - ultimaLeitura) > leituraDelay)
    {
        if (irrecv.decode(&resultados))
        {
            valor = resultados.decode_type == NEC ? resultados.value : valor;
            irrecv.resume(); // Recebe o próximo valor
        }
        ultimaLeitura = agora;
    }
    return valor;
}

void iniciaIR()
{
    irrecv.enableIRIn();
}

unsigned int irComando()
{
    unsigned int retorno = 0;
    long botao = lerIR();

    if (botao > 0)
    {
        switch (botao)
        {
        case AlexaApagaTudo:
        case IrPower:
            retorno = 1;
            break;

        case AlexaFundos:
        case Ir1:
            retorno = 2;
            break;

        case AlexaDispensa:
        case Ir2:
            retorno = 3;
            break;

        case AlexaCozinha:
        case IrTv:
        case Ir3:
            retorno = 4;
            break;

        case AlexaSofa:
        case Ir4:
            retorno = 5;
            break;

        case AlexaPorta:
        case Ir5:
            retorno = 6;
            break;

        case AlexaSalaTres:
        case Ir6:
            retorno = 7;
            break;

        case AlexaSalaQuatro:
        case Ir7:
            retorno = 8;
            break;

        case AlexaGaragem:
        case Ir9:
            retorno = 9;
            break;

        case AlexaPortaEntrada:
        case Ir0:
            retorno = 10;
            break;

        case AlexaLampiao:
        case IrAzul:
            retorno = 11;
            break;

        case AlexaModoNoturno:
        case IrAmarelo:
            retorno = 12;
            break;

        case IrVerde:
            retorno = 13;
            break;

        case IrVolmais:
            retorno = 14;
            break;

        case IrVolmenos:
            retorno = 15;
            break;

        case IrQview:
            retorno = 16;
            break;

        case IrMute:
            retorno = 17;
            break;

        case AlexaAcendeTudo:
        case IrOk:
            retorno = 18;
            break;

        default:
            break;
        }
    }

    return retorno;
}
