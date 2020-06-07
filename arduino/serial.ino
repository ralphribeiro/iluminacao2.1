bool mensagemPronta = false;
String mensagem = "";

void iniciaSerial()
{
    Serial.begin(74880);
}

String verificaMensagemSerial()
{
    String retorno = "";
    eventoSerial();

    if (mensagemPronta)
    {
        retorno = mensagem;

        limpaMensagem();
    }

    return retorno;
}

void enviaMensagemSerial(String msg)
{
    // String msgEnvio = "";
    // msgEnvio = (String)volts + "," + (String)amperes;
    Serial.println(msg);
}

void eventoSerial()
{
    while (Serial.available())
    {
        char entrada = (char)Serial.read();

        if (entrada == '\n')
        {
            mensagemPronta = true;
            mensagem = mensagem.substring(0, mensagem.length() - 1);
        }
        else
            mensagem += entrada;
    }
}

void limpaMensagem()
{
    mensagemPronta = false;
    mensagem = "";
}