#include <Led.h>

unsigned short int pinBotao1 = 12;
unsigned short int pinPSON = 13;
unsigned short int pinIR = 4;
unsigned short int pinRele1 = A0;
unsigned short int pinRele2 = A1;
unsigned short int pinRele3 = A2;
unsigned short int pinRele4 = A3;
unsigned short int pinMosfet1 = 10;
unsigned short int pinMosfet2 = 9;
unsigned short int pinMosfet3 = 6;
unsigned short int pinMosfet4 = 5;
unsigned short int pinMosfet5 = 3;

unsigned short int RELE = 0;
unsigned short int MOSFET = 1;

unsigned short int nivelMin = 10;
unsigned short int nivelMax = 240;

unsigned int intervaloEventoFade = 30;
unsigned short int degrauFade = 5;

Led ledFundos(pinRele1, RELE, HIGH, LOW);
Led ledCorredoFundos(pinRele2, RELE, HIGH, LOW);
Led ledCozinha(pinRele3, RELE, HIGH, LOW);
Led ledCortesia(pinRele4, RELE, HIGH, LOW);

Led ledSalaUm(pinMosfet1, MOSFET, nivelMin, nivelMax);
Led ledSalaDois(pinMosfet2, MOSFET, nivelMin, nivelMax);
Led ledSalaTres(pinMosfet3, MOSFET, nivelMin, nivelMax);
Led ledSalaQuatro(pinMosfet4, MOSFET, nivelMin, nivelMax);
Led ledBico(pinMosfet5, RELE, LOW, HIGH);

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
	ledFundos.apaga();
	ledCorredoFundos.apaga();
	ledCozinha.apaga();
	ledCortesia.apaga();
	ledSalaUm.apaga();
	ledSalaDois.apaga();
	ledSalaTres.apaga();
	ledSalaQuatro.apaga();
	ledBico.apaga();
	gerenciaFonte();
}

void gerenciaFonte(){
  algumLedAceso() ? ligaFonte() : desligaFonte();			
}

bool algumLedAceso(){
	if (ledFundos.aceso() ||
		ledCorredoFundos.aceso() ||
		ledCozinha.aceso() ||
		ledCortesia.aceso() ||
		ledSalaUm.aceso() ||
		ledSalaDois.aceso() ||
		ledSalaTres.aceso() ||
		ledSalaQuatro.aceso() ||
		ledBico.aceso()){

		return true;
	}
	return false;
}

void manipulaNivelMin(){
	if (ledSalaUm.obtemNivel() == nivelMin &&
		ledSalaDois.obtemNivel() == nivelMin &&
		ledSalaTres.obtemNivel() == nivelMin &&
		ledSalaQuatro.obtemNivel() == nivelMin){

		ledSalaUm.apaga();
		ledSalaDois.apaga();
		ledSalaTres.apaga();
		ledSalaQuatro.apaga();
	}
	else{
		ledSalaUm.apaga();
		ledSalaDois.apaga();
		ledSalaTres.apaga();
		ledSalaQuatro.apaga();

		ledSalaUm.nivelMinimo();
		ledSalaDois.nivelMinimo();
		ledSalaTres.nivelMinimo();
		ledSalaQuatro.nivelMinimo();
	}
}

void manipulaFade(){
	if (!ledSalaUm.fade() &&
		!ledSalaDois.fade() &&
		!ledSalaTres.fade() &&
		!ledSalaQuatro.fade()){

		if (!ledSalaUm.aceso() &&
			!ledSalaDois.aceso() &&
			!ledSalaTres.aceso() &&
			!ledSalaQuatro.aceso()){

			ledSalaUm.ativaFade(HIGH, degrauFade, intervaloEventoFade);
			ledSalaDois.ativaFade(HIGH, degrauFade, intervaloEventoFade);
			ledSalaTres.ativaFade(HIGH, degrauFade, intervaloEventoFade);
			ledSalaQuatro.ativaFade(HIGH, degrauFade, intervaloEventoFade);
		}
		else{
			ledSalaUm.ativaFade(LOW, degrauFade, intervaloEventoFade);
			ledSalaDois.ativaFade(LOW, degrauFade, intervaloEventoFade);
			ledSalaTres.ativaFade(LOW, degrauFade, intervaloEventoFade);
			ledSalaQuatro.ativaFade(LOW, degrauFade, intervaloEventoFade);
		}
	}
}

void gerenciaBotao(){
	unsigned short int retorno = processaBotao();

	if (retorno > 0){
		switch (retorno){
		case 1:
			ledCortesia.aceso() ? ledCortesia.apaga() : ledCortesia.acende();
			break;

		case 2:
			ledBico.aceso() ? ledBico.apaga() : ledBico.acende();
			break;

		case 3:
			ledBico.ativaTemporizador(120000);
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
	if (ledSalaUm.processa() ||
		ledSalaDois.processa() ||
		ledSalaTres.processa() ||
		ledSalaQuatro.processa() ||
		ledBico.processa()){

		gerenciaFonte();
	}
}

void gerenciaSerial(){
	String msg = verificaMensagemSerial();

	if (msg.compareTo("") > 0){
		if (msg == "#LS"){
			ledFundos.aceso() ? ledFundos.apaga() : ledFundos.acende();
		}

		gerenciaFonte();
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
			ledFundos.aceso() ? ledFundos.apaga() : ledFundos.acende();
			break;

		case 3:
			ledCorredoFundos.aceso() ? ledCorredoFundos.apaga() : ledCorredoFundos.acende();
			break;

		case 4:
			ledCozinha.aceso() ? ledCozinha.apaga() : ledCozinha.acende();
			break;

		case 5:
			ledSalaUm.aceso() ? ledSalaUm.apaga() : ledSalaUm.acende();
			break;

		case 6:
			ledSalaDois.aceso() ? ledSalaDois.apaga() : ledSalaDois.acende();
			break;

		case 7:
			ledSalaTres.aceso() ? ledSalaTres.apaga() : ledSalaTres.acende();
			break;

		case 8:
			ledSalaQuatro.aceso() ? ledSalaQuatro.apaga() : ledSalaQuatro.acende();
			break;

		case 9:
			ledBico.aceso() ? ledBico.apaga() : ledBico.acende();
			break;

		case 10:
			ledCortesia.aceso() ? ledCortesia.apaga() : ledCortesia.acende();
			break;

		case 11:
			if (ledSalaTres.aceso())
				ledSalaTres.obtemNivel() != nivelMin ? ledSalaTres.apaga() : ledSalaTres.nivelMinimo();
			else
				ledSalaTres.nivelMinimo();

			break;

		case 12:
			manipulaNivelMin();
			break;

		case 16:
			manipulaFade();
			break;

		case 17:
			ledBico.ativaTemporizador(60000);
			break;

		default:
			break;
		}

		gerenciaFonte();
	}
}
