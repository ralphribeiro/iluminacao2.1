extern unsigned short int pinBotao1;

unsigned short int estadoBotao;
unsigned short int ultimoEstadoBotao = HIGH;

unsigned long ultimoEvento = 0;
unsigned int intervaloEvento = 25;

bool botaoFlag = false;

void iniciaBotao()
{
    pinMode(pinBotao1, INPUT_PULLUP);
}

bool apertouBotao()
{
    bool pressionou = false;
    int valorLido = digitalRead(pinBotao1);

    if (valorLido != ultimoEstadoBotao)
        ultimoEvento = millis();

    if ((millis() - ultimoEvento) > intervaloEvento)
    {
        if (valorLido != estadoBotao)
        {
            estadoBotao = valorLido;

            if (estadoBotao == LOW)
            {
                pressionou = true;
                botaoFlag = !botaoFlag;
            }
        }
    }

    ultimoEstadoBotao = valorLido;

    return pressionou;
}

bool flagAtivada()
{
    return botaoFlag;
}