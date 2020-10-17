bool PSONState = HIGH;

extern uint8_t pinPSON;

void iniciaFonte(){
    PSONState = LOW;
    desligaFonte();
}

void ligaFonte(){
    if (PSONState == LOW)
        return;

    PSONState = LOW;
    digitalWrite(pinPSON, PSONState);
}

void desligaFonte(){
    if (PSONState == HIGH)
        return;

    PSONState = HIGH;
    digitalWrite(pinPSON, PSONState);
}

bool fonteLigada(){
    return PSONState == LOW ? true : false;
}
