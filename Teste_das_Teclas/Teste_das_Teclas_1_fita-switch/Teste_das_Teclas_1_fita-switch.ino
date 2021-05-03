#include <IRremote.h>
#include <Adafruit_NeoPixel.h> // Biblioteca para controle da fita LED
// Necessário para Trinket Adafruit de 16 MHz
#ifdef __AVR__
#include <avr/power.h>
#endif

#define DATA_PIN 2  // Pino de E/S digital conectado aos NeoPixels.
#define NUM_LEDS 11 // Número de LEDs na fita


int RECV_PIN = 4;
int codigo;
int codigoO;



IRrecv receptor(RECV_PIN);
decode_results resultado;

// FUNCTION RESET ARDUINO
void (*funcReset)() = 0;

// Cria um "objeto" Adafruit_NeoPixel (Fita LED)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ800);


void setup()
{
  // Estas linhas são especificamente para suportar a Adafruit Trinket 5V 16 MHz.
  // Qualquer outra placa, você pode remover esta parte (mas nenhum dano deixando-a)
#if defined(__AVR_ATtiny85__)
  if (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
#endif
  // FIM do código específico do Trinket.
  Serial.begin(9600);       //frequência da porta serial
  strip.begin();            //Inicialize o objeto de tira NeoPixel (NECESSÁRIO)
  strip.show();             //DESLIGUE todos os pixels o mais rápido possível
  strip.setBrightness(50); //Brilho da tira
  receptor.enableIRIn(); // Inicializa o receptor IR

}

void loop()
{
  if (receptor.decode(&resultado))
  {
    Serial.print("Codigo do botao: ");
    Serial.println(resultado.value, HEX);
    codigoO = resultado.value;
    switch (codigoO)
    {
      case (0xE318261B):
        colorWipe(0x00, 0xff, 0xff, 50); //Ciano
        break;
      case (0xFF629D):
        rainbowCycle(30);
        break;
      case (0xFFE21D):
        RunningLights(0xff, 0x00, 0x00, 50); //red
        break;
      case (0xFF38C7): //Apaga todos os leds
        funcReset(); //Reset
        break;
      default:
        Serial.print("-Codigo do Botao Inexistente-");
        Serial.println(resultado.value, HEX);
    }
  }
  receptor.resume();

  delay(100);
}


void colorWipe(byte red, byte green, byte blue, int SpeedDelay)
{
  for (uint16_t i = 0; i < NUM_LEDS; i++)
  {
    setPixel(i, red, green, blue);
    if (receptor.decode(&resultado))
    {
      Serial.print("Codigo do botao: ");
      Serial.println(resultado.value, HEX);
      codigo = resultado.value;
      switch (codigo)
      {
        // case (0xE318261B):
        //     colorWipe(0x00, 0xff, 0xff, 50); //Ciano
        //     break;
        case (0xFF629D):
          rainbowCycle(30);
          break;
        case (0xFFE21D):
          RunningLights(0xff, 0x00, 0x00, 50); //red
          break;
        case (0xFF38C7): //Apaga todos os leds
          funcReset(); //Reset
          break;
        default:
          Serial.print("-Codigo do Botao Inexistente-");
          Serial.println(resultado.value, HEX);
      }
    }
    showStrip();
    delay(SpeedDelay);
  }
}

void rainbowCycle(int SpeedDelay)
{
  byte *c;
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++)
  { // 5 ciclos de todas as cores na roda
    for (i = 0; i < NUM_LEDS; i++)
    {
      c = Wheel(((i * 256 / NUM_LEDS) + j) & 255);
      setPixel(i, *c, *(c + 1), *(c + 2));
      if (receptor.decode(&resultado))
      {
        Serial.print("Codigo do botao: ");
        Serial.println(resultado.value, HEX);
        codigo = resultado.value;
        switch (codigo)
        {
          case (0xE318261B):
            colorWipe(0x00, 0xff, 0xff, 50); //Ciano
            break;
          // case (0xFF629D):
          //     rainbowCycle(30);
          //     break;
          case (0xFFE21D):
            RunningLights(0xff, 0x00, 0x00, 50); //red
            break;
          case (0xFF38C7): //Apaga todos os leds
            funcReset(); //Reset
            break;
          default:
            Serial.print("-Codigo do Botao Inexistente-");
            Serial.println(resultado.value, HEX);
        }
      }
    }
    showStrip();
    delay(SpeedDelay);
  }
}
byte *Wheel(byte WheelPos) /*PERTENCE A RAINBOW CYCLE*/
{
  static byte c[3];

  if (WheelPos < 85)
  {
    c[0] = WheelPos * 3;
    c[1] = 255 - WheelPos * 3;
    c[2] = 0;
  }
  else if (WheelPos < 170)
  {
    WheelPos -= 85;
    c[0] = 255 - WheelPos * 3;
    c[1] = 0;
    c[2] = WheelPos * 3;
  }
  else
  {
    WheelPos -= 170;
    c[0] = 0;
    c[1] = WheelPos * 3;
    c[2] = 255 - WheelPos * 3;
  }

  return c;
}


void RunningLights(byte red, byte green, byte blue, int WaveDelay)
{
  int Position = 0;

  for (int i = 0; i < NUM_LEDS * 2; i++)
  {
    Position++; // = 0; //Position + Rate;
    //= 0; //Posição + Taxa;
    for (int i = 0; i < NUM_LEDS; i++)
    {
      //  onda seno, 3 ondas offset fazem um arco-íris!
      //  float level = sin(i+Position) * 127 + 128;
      //  setPixel(i,level,0,0);
      //  float level = sin(i+Position) * 127 + 128;
      setPixel(i, ((sin(i + Position) * 127 + 128) / 255) * red,
               ((sin(i + Position) * 127 + 128) / 255) * green,
               ((sin(i + Position) * 127 + 128) / 255) * blue);
      if (receptor.decode(&resultado))
      {
        Serial.print("Codigo do botao: ");
        Serial.println(resultado.value, HEX);
        codigo = resultado.value;
        switch (codigo)
        {
          case (0xE318261B):
            colorWipe(0x00, 0xff, 0xff, 50); //Ciano
            break;
          case (0xFF629D):
            rainbowCycle(30);
            break;
          // case (0xFFE21D):
          //     RunningLights(0xff, 0x00, 0x00, 50); //red
          //     break;
          case (0xFF38C7): //Apaga todos os leds
            funcReset(); //Reset
            break;
          default:
            Serial.print("-Codigo do Botao Inexistente-");
            Serial.println(resultado.value, HEX);
        }
      }
      showStrip();
      delay(WaveDelay);
    }
  }
}

// ***NOT REPLACE HERE DOWN***
void showStrip()
{
#ifdef ADAFRUIT_NEOPIXEL_H
  // NeoPixel
  strip.show();
#endif
#ifndef ADAFRUIT_NEOPIXEL_H
  // FastLED
  FastLED.show();
#endif
}
void setPixel(int Pixel, byte red, byte green, byte blue)
{
#ifdef ADAFRUIT_NEOPIXEL_H
  // NeoPixel
  strip.setPixelColor(Pixel, strip.Color(red, green, blue));
#endif
#ifndef ADAFRUIT_NEOPIXEL_H
  // FastLED
  leds[Pixel].r = red;
  leds[Pixel].g = green;
  leds[Pixel].b = blue;
#endif
}
void setAll(byte red, byte green, byte blue)
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    setPixel(i, red, green, blue);
  }
  showStrip();
}
