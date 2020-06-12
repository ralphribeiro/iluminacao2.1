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
// Led ledBico(pinMosfet5, MOSFET, nivelMin, nivelMax);

void setup()
{
	iniciaFonte();
	iniciaIR();
	iniciaBotao();
	iniciaSerial();
	// Serial.begin(9600);
	// pinMode(pinMosfet5, OUTPUT);
}

void loop()
{
	gerenciaEventoIR();

	if (apertouBotao())
	{
		if (!ledCortesia.aceso())
			ledCortesia.acende();
		else
			ledCortesia.apaga();

		gerenciaFonte();
	}

	gerenciaSerial();

	gerenciaFade();
}

void gerenciaFade()
{
	if (ledSalaUm.processaFade() ||
		ledSalaDois.processaFade() ||
		ledSalaTres.processaFade() ||
		ledSalaQuatro.processaFade()) //||
		// ledBico.processaFade())
	{
		gerenciaFonte();
	}
}

void gerenciaSerial()
{
	String msg = verificaMensagemSerial();

	if (msg.compareTo("") > 0)
	{
		if (msg == "#LS")
		{
			if (!ledFundos.aceso())
				ledFundos.acende();
			else
				ledFundos.apaga();
		}

		gerenciaFonte();
	}
}

void gerenciaEventoIR()
{
	unsigned int comando = irComando();

	if (comando > 0)
	{
		switch (comando)
		{
		case 1:
			desliga();
			break;

		case 2:
			if (!ledFundos.aceso())
				ledFundos.acende();
			else
				ledFundos.apaga();
			break;

		case 3:
			if (!ledCorredoFundos.aceso())
				ledCorredoFundos.acende();
			else
				ledCorredoFundos.apaga();
			break;

		case 4:
			if (!ledCozinha.aceso())
				ledCozinha.acende();
			else
				ledCozinha.apaga();
			break;

		case 5:
			if (!ledSalaUm.aceso())
				ledSalaUm.acende();
			else
				ledSalaUm.apaga();
			break;

		case 6:
			if (!ledSalaDois.aceso())
				ledSalaDois.acende();
			else
				ledSalaDois.apaga();
			break;

		case 7:
			if (!ledSalaTres.aceso())
				ledSalaTres.acende();
			else
				ledSalaTres.apaga();
			break;

		case 8:
			if (!ledSalaQuatro.aceso())
				ledSalaQuatro.acende();
			else
				ledSalaQuatro.apaga();
			break;

		case 9:
			// if (!ledBico.aceso())
			// 	ledBico.acende();
			// else
			// 	ledBico.apaga();
			// digitalWrite(pinMosfet5, !digitalRead(pinMosfet5));

			break;

		case 10:
			if (!ledCortesia.aceso())
				ledCortesia.acende();
			else
				ledCortesia.apaga();
			break;

		case 11:
			if (!ledSalaTres.aceso())
				ledSalaTres.apaga();

			ledSalaTres.nivelMinimo();
			break;
		
		case 16:
			if (!ledSalaQuatro.fade())
			{
				if (!ledSalaQuatro.aceso())
					ledSalaQuatro.ativaFade(HIGH, degrauFade, intervaloEventoFade);
				else
					ledSalaQuatro.ativaFade(LOW, degrauFade, intervaloEventoFade);

				ledSalaQuatro.processaFade();
			}
			break;

		default:
			break;
		}

		gerenciaFonte();
	}
}

void desliga()
{
	ledFundos.apaga();
	ledCorredoFundos.apaga();
	ledCozinha.apaga();
	ledCortesia.apaga();
	ledSalaUm.apaga();
	ledSalaDois.apaga();
	ledSalaTres.apaga();
	ledSalaQuatro.apaga();
	// ledBico.apaga();
	gerenciaFonte();
}

void gerenciaFonte()
{
	if (algumLedAceso())
		ligaFonte();
	else
		desligaFonte();
}

bool algumLedAceso()
{
	if (ledFundos.aceso() ||
		ledCorredoFundos.aceso() ||
		ledCozinha.aceso() ||
		ledCortesia.aceso() ||
		ledSalaUm.aceso() ||
		ledSalaDois.aceso() ||
		ledSalaTres.aceso() ||
		ledSalaQuatro.aceso()) // ||
		// ledBico.aceso())
	{
		return true;
	}

	return false;
}