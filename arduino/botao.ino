extern uint8_t pinBotao1;

#define UMTOQUE 1
#define DOISTOQUES 2
#define TRESTOQUES 3
#define QUATROTOQUES 4
#define BOTAOPRESO 5
#define UMTOQUEEPRESO 6

unsigned short int ultimoEstadoBotao = HIGH;
unsigned long ultimoEvento = 0;
unsigned int intervaloEvento = 25;
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

	ultimoEvento = valorLido != ultimoEstadoBotao ? millis() : ultimoEvento;

	if ((millis() - ultimoEvento) > intervaloEvento)
		estadoBotao = valorLido != estadoBotao ? valorLido : estadoBotao;

	//pressionado
	if (estadoBotao == 0 && flag2 == 0)
	{
		tempoPressionado = millis();
		flag1 = 0;
		flag2 = 1;
		contadorToque++;
	}

	//solto
	if (estadoBotao == 1 && flag1 == 0)
	{
		tempoSoltura = millis();
		flag1 = 1;
		flag2 = 0;

		tempoDelta = tempoSoltura - tempoPressionado;
	}

	if ((millis() - tempoPressionado) > tempoEsperaEvento && estadoBotao == 1)
	{
		if (contadorToque == 1)
			retorno = tempoDelta >= tempoEsperaEvento ? BOTAOPRESO : UMTOQUE;
		else if (contadorToque == 2)
			retorno = tempoDelta >= tempoEsperaEvento ? UMTOQUEEPRESO : DOISTOQUES;
		else if (contadorToque == 3)
			retorno = TRESTOQUES;
		else if (contadorToque == 4)
			retorno = QUATROTOQUES;

		contadorToque = 0;
	}
	ultimoEstadoBotao = valorLido;

	return retorno;
}
