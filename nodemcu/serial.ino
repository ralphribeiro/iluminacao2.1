#include <SoftwareSerial.h>

#define RX1 15
#define TX1 13

unsigned int intervaloSerial = 1000;
long ultimoEventoSerial = 0;

bool mensagemPronta = false;
String mensagem = "";

String comandoSerial = "";

SoftwareSerial nano(RX1, TX1);

void iniciaSerial(){
	Serial.begin(115200);
    nano.begin(74880);
}

void processaSerial(){
	processaEnvio();
	processaRecebimento();
}

void processaRecebimento(){
    eventoSerial();

    if(mensagemPronta){
        Serial.print(mensagem);
        limpaMensagem();
    }  
}

void processaEnvio(){
	long millisAgora = millis();

    if ((millisAgora - ultimoEventoSerial) > intervaloSerial){

		nano.println("#VA");
        
        ultimoEventoSerial = millisAgora;
    }
}

void eventoSerial(){    
    while(nano.available()){
    char entrada = (char)nano.read();
        if(entrada == '\n')
            mensagemPronta = true;
        else
            mensagem += entrada;
    }    
}

void limpaMensagem(){
    mensagemPronta = false;
    mensagem = "";
}