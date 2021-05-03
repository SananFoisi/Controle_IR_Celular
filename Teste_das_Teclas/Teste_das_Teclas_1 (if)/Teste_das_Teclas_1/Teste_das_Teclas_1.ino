// Programa : Teste Controle Remoto IR
// Autor : Arduino e Cia

#include <IRremote.h>

int RECV_PIN = 2;
float armazenavalor;
int pinoledvermelho = 5;
int pinoledazul = 6;
int pinoledverde = 7;

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  pinMode(pinoledvermelho, OUTPUT);
  pinMode(pinoledazul, OUTPUT);
  pinMode(pinoledverde, OUTPUT);
  Serial.begin(9600);
  irrecv.enableIRIn(); // Inicializa o receptor IR
}

void loop()
{
  if (irrecv.decode(&results))
  {
    Serial.print("Valor lido : ");
    Serial.println(results.value, HEX);

    armazenavalor = (results.value);
    if (armazenavalor == 0xFFA25D) //Verifica se a tecla 1 foi acionada
    {
      digitalWrite(pinoledvermelho, HIGH);  //Acende o led vermelho
    }

    if (armazenavalor == 0xFF629D) //Verifica se a tecla 4 foi acionada
    {
      digitalWrite(pinoledverde, HIGH); //Acende o led verde
    }

    if (armazenavalor == 0xFFE21D) //Verifica se a tecla 4 foi acionada
    {
      digitalWrite(pinoledazul, HIGH); //Acende o led verde
    }


    /*
        if (armazenavalor == oxFFE21D) //Verifica se a tecla 9 foi acionada
        {
          digitalWrite(pinoledvermelho, LOW); //Apaga todos os leds
          digitalWrite(pinoledverde, LOW);
        }
    */
    irrecv.resume(); //Le o próximo valor
  }
}
