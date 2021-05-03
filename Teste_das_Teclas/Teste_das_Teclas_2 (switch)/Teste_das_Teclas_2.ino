#include <IRremote.h>

int RECV_PIN = 2;
int codigo;
int pinoledvermelho = 5;
int pinoledazul = 6;
int pinoledverde = 7;

IRrecv receptor(RECV_PIN);
decode_results resultado;

void setup()
{
  pinMode(pinoledvermelho, OUTPUT);
  pinMode(pinoledazul, OUTPUT);
  pinMode(pinoledverde, OUTPUT);
  receptor.enableIRIn();
  Serial.begin(9600);
}

void loop()
{
  if (receptor.decode(&resultado))
  {
    Serial.print("Codigo do botao: ");
    Serial.println(resultado.value, HEX);
    codigo = resultado.value;
    switch (codigo)
    {
      case (0xFFA25D):
        digitalWrite(pinoledvermelho, HIGH);  //Acende o led vermelho
        break;
      case (0xFF629D):
        digitalWrite(pinoledverde, HIGH); //Acende o led verde
        break;
      case (0xFFE21D):
        digitalWrite(pinoledazul, HIGH); //Acende o led verde
        break;
      case (0xFF38C7):
        digitalWrite(pinoledvermelho, LOW); //Apaga todos os leds
        digitalWrite(pinoledverde, LOW);
        digitalWrite(pinoledazul, LOW); //Acende o led verde
        break;
      default:
        Serial.print("-Tecla Inexistente-");
        Serial.print("Codigo do botao: ");
        Serial.println(resultado.value, HEX);

    }
  }
  receptor.resume();

  delay(100);
}
