bool mensagemPronta = false;
String mensagem = "";

void iniciaSerial(){
    Serial.begin(74880); 
}

void processaSerial(){
    eventoSerial();

    if(mensagemPronta){

        if(mensagem == "#VA"){
            String msgEnvio = "";
            //msgEnvio = (String)volts + "," + (String)amperes;
            Serial.println(msgEnvio);
        }
        limpaMensagem();
    }
}

void eventoSerial(){    
    while(Serial.available()){
    char entrada = (char)Serial.read();

        if(entrada == '\n'){
            mensagemPronta = true;
            mensagem = mensagem.substring(0, mensagem.length() - 1);
        }
        else
            mensagem += entrada;
    }
}

void limpaMensagem(){
    mensagemPronta = false;
    mensagem = "";
}