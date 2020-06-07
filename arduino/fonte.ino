unsigned short int PSONState = HIGH;

extern unsigned short int pinPSON;

void iniciaFonte()
{
    desligaFonte();
}

void ligaFonte()
{
    PSONState = LOW;
    digitalWrite(pinPSON, PSONState);
}

void desligaFonte()
{
    PSONState = HIGH;
    digitalWrite(pinPSON, PSONState);
}

bool fonteLigada()
{
    if (PSONState == LOW)
        return true;
    else
        return false;
}