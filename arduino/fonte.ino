unsigned short int PSONState = HIGH;

extern unsigned short int pinPSON;

void iniciaFonte()
{
    PSONState = LOW;
    desligaFonte();
}

void ligaFonte()
{
    if (PSONState == LOW)
        return;

    PSONState = LOW;
    digitalWrite(pinPSON, PSONState);
}

void desligaFonte()
{
    if (PSONState == HIGH)
        return;

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