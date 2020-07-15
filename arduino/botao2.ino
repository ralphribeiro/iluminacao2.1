extern unsigned short int pinBotao1;

#define UMTOQUE 1
#define DOISTOQUES 2
#define TRESTOQUES 3
#define QUATROTOQUES 4
#define BOTAOPRESO 5
#define UMTOQUEEPRESO 6

unsigned short int ultimoEstadoBotao = HIGH;
unsigned long ultimoEvento = 0;
unsigned int intervaloEvento = 50;
unsigned int tempoEsperaEvento = 400;
bool estadoBotao = HIGH;
byte contadorToque;
int tempoDelta;
bool flag1, flag2;
long double tempoPressionado, tempoSoltura;


void iniciaBotao()
{
	pinMode(pinBotao1, INPUT_PULLUP);
}

unsigned short int processaBotao()
{
	unsigned short int retorno = 0;

	int valorLido = digitalRead(pinBotao1);

	if (valorLido != ultimoEstadoBotao)
		ultimoEvento = millis();

	if ((millis() - ultimoEvento) > intervaloEvento)
	{
		if (valorLido != estadoBotao)
		{
			estadoBotao = valorLido;
		}
	}

	//when switch is pressed
	if (estadoBotao == 0 && flag2 == 0)
	{
		tempoPressionado = millis(); //time from millis fn will save to presstime variable
		flag1 = 0;
		flag2 = 1;
		contadorToque++; //tap counter will increase by 1
	}

	//when sw is released
	if (estadoBotao == 1 && flag1 == 0)
	{
		tempoSoltura = millis(); //time from millis fn will be saved to releasetime var
		flag1 = 1;
		flag2 = 0;

		tempoDelta = tempoSoltura - tempoPressionado; //here we find the time gap between press and release and stored to timediff var
	}

	if ((millis() - tempoPressionado) > tempoEsperaEvento && estadoBotao == 1) //wait for some time and if sw is in release position
	{
		if (contadorToque == 1) //if tap counter is 1
		{
			if (tempoDelta >= tempoEsperaEvento) //if time diff is larger than 400 then its a hold
				retorno = BOTAOPRESO;
			else //if timediff is less than 400 then its a single tap
				retorno = UMTOQUE;
		}
		else if (contadorToque == 2) //if tapcounter is 2
		{
			if (tempoDelta >= tempoEsperaEvento) // if timediff is greater than  400 then its single tap and hold
				retorno = UMTOQUEEPRESO;
			else // if timediff is less than 400 then its just double tap
				retorno = DOISTOQUES;
		}
		else if (contadorToque == 3) //if tapcounter is 3 //then its triple tap
			retorno = TRESTOQUES;
		else if (contadorToque == 4) //if tapcounter is 4 then its 4 tap
			retorno = QUATROTOQUES;

		contadorToque = 0;
	}
	ultimoEstadoBotao = valorLido;
}