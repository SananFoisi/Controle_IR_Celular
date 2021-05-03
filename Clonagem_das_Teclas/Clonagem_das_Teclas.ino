#include <IRremote.h> //INCLUSÃO DE BIBLIOTECA

int RECV_PIN = 2; //PINO DIGITAL UTILIZADO PELO FOTORRECEPTOR KY-022

IRrecv irrecv(RECV_PIN); //PASSA O PARÂMETRO PARA A FUNÇÃO irrecv

decode_results results; //VARIÁVEL QUE ARMAZENA OS RESULTADOS (SINAL IR RECEBIDO)

void setup() {
  Serial.begin(9600); //INICIALIZA A SERIAL
  irrecv.enableIRIn(); //INICIALIZA A RECEPÇÃO DE SINAIS IR
}

void loop() {
  //CAPTURA O SINAL IR
  if (irrecv.decode(&results)) {
    //Serial.print("Código HEX: "); //IMPRIME O TEXTO NO MONITOR SERIAL
    Serial.println(results.value, HEX); //IMPRIME NO MONITOR SERIAL O CÓDIGO IR EM FORMATO HEXADECIMAL
    //Serial.print("Código DEC: "); //IMPRIME O TEXTO NO MONITOR SERIAL
    Serial.println(results.value); //IMPRIME NO MONITOR SERIAL O CÓDIGO IR EM FORMATO DECIMAL
    Serial.println(""); //QUEBRA DE LINHA NA SERIAL
    irrecv.resume(); //AGUARDA O RECEBIMENTO DE UM NOVO SINAL IR
  }
  delay(100); //INTERVALO DE 100 MILISSEGUNDOS
}
