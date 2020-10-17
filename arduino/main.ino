#include <Led.h>

unsigned short int pinBotao1 = 12;
unsigned short int pinPSON = 13;
unsigned short int pinIR = 4;
unsigned short int pinRele1 = A0;
unsigned short int pinRele2 = A1;
unsigned short int pinRele3 = A2;
unsigned short int pinRele4 = A3;
unsigned short int pinRele5 = 3;
unsigned short int pinMosfet1 = 10;
unsigned short int pinMosfet2 = 9;
unsigned short int pinMosfet3 = 6;
unsigned short int pinMosfet4 = 5;

unsigned short int RELE = 0;
unsigned short int MOSFET = 1;

unsigned short int nivelMin = 10;
unsigned short int nivelMax = 240;

unsigned int intervaloEventoFade = 30;
unsigned short int degrauFade = 5;

// Led ledFundos(pinRele1, RELE, HIGH, LOW);
// Led ledCorredoFundos(pinRele2, RELE, HIGH, LOW);
// Led ledCozinha(pinRele3, RELE, HIGH, LOW);
// Led ledCortesia(pinRele4, RELE, HIGH, LOW);

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
	Led(pinRele5, RELE, LOW, HIGH)
};

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
	ledsRele[ledFundos].apaga();
	ledsRele[ledCorredoFundos].apaga();
	ledsRele[ledCozinha].apaga();
	ledsRele[ledCortesia].apaga();
	ledsRele[ledBico].apaga();
	ledsMosfet[ledSalaUm].apaga();
	ledsMosfet[ledSalaDois].apaga();
	ledsMosfet[ledSalaTres].apaga();
	ledsMosfet[ledSalaQuatro].apaga();
	gerenciaFonte();
}

void gerenciaFonte(){
  algumLedAceso() ? ligaFonte() : desligaFonte();			
}

bool algumLedAceso(){
	if (ledsRele[ledFundos].aceso() ||
		ledsRele[ledCorredoFundos].aceso() ||
		ledsRele[ledCozinha].aceso() ||
		ledsRele[ledCortesia].aceso() ||
		ledsRele[ledBico].aceso() ||
		ledsMosfet[ledSalaUm].aceso() ||
		ledsMosfet[ledSalaDois].aceso() ||
		ledsMosfet[ledSalaTres].aceso() ||
		ledsMosfet[ledSalaQuatro].aceso()){

		return true;
	}
	return false;
}

void manipulaNivelMin(){
	if (ledsMosfet[ledSalaUm].obtemNivel() == nivelMin &&
		ledsMosfet[ledSalaDois].obtemNivel() == nivelMin &&
		ledsMosfet[ledSalaTres].obtemNivel() == nivelMin &&
		ledsMosfet[ledSalaQuatro].obtemNivel() == nivelMin){

		ledsMosfet[ledSalaUm].apaga();
		ledsMosfet[ledSalaDois].apaga();
		ledsMosfet[ledSalaTres].apaga();
		ledsMosfet[ledSalaQuatro].apaga();
	}
	else{
		ledsMosfet[ledSalaUm].apaga();
		ledsMosfet[ledSalaDois].apaga();
		ledsMosfet[ledSalaTres].apaga();
		ledsMosfet[ledSalaQuatro].apaga();

		ledsMosfet[ledSalaUm].nivelMinimo();
		ledsMosfet[ledSalaDois].nivelMinimo();
		ledsMosfet[ledSalaTres].nivelMinimo();
		ledsMosfet[ledSalaQuatro].nivelMinimo();
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

			ledsMosfet[ledSalaUm].ativaFade(HIGH, degrauFade, intervaloEventoFade);
			ledsMosfet[ledSalaDois].ativaFade(HIGH, degrauFade, intervaloEventoFade);
			ledsMosfet[ledSalaTres].ativaFade(HIGH, degrauFade, intervaloEventoFade);
			ledsMosfet[ledSalaQuatro].ativaFade(HIGH, degrauFade, intervaloEventoFade);
		}
		else{
			ledsMosfet[ledSalaUm].ativaFade(LOW, degrauFade, intervaloEventoFade);
			ledsMosfet[ledSalaDois].ativaFade(LOW, degrauFade, intervaloEventoFade);
			ledsMosfet[ledSalaTres].ativaFade(LOW, degrauFade, intervaloEventoFade);
			ledsMosfet[ledSalaQuatro].ativaFade(LOW, degrauFade, intervaloEventoFade);
		}
	}
}

void gerenciaBotao(){
	unsigned short int retorno = processaBotao();

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
		if (msg == "#LS"){
			// ledsRele[ledFundos].aceso() ? ledsRele[ledFundos].apaga() : ledsRele[ledFundos].acende();
		}

		gerenciaFonte();
	}
}

void acendeTodos(){
	ledsRele[ledFundos].acende();
	ledsRele[ledCorredoFundos].acende();
	ledsRele[ledCozinha].acende();
	ledsRele[ledCortesia].acende();
	ledsRele[ledBico].acende();
	ledsMosfet[ledSalaUm].acende();
	ledsMosfet[ledSalaDois].acende();
	ledsMosfet[ledSalaTres].acende();
	ledsMosfet[ledSalaQuatro].acende();
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
