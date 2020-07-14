unsigned short int pinMosfet5 = 3;

unsigned short int MOSFET = 1;

unsigned short int nivelMin = 10;
unsigned short int nivelMax = 240;

unsigned int intervaloEventoFade = 30;
unsigned short int degrauFade = 5;

Led ledBico(pinMosfet5, MOSFET, nivelMin, nivelMax);

void setup()
{
	iniciaSerial();
}


void loop()
{

}