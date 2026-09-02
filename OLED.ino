#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define i2c_Address 0x3C

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

const int LM35 = A0;
int lectura;
float temperatura;

Adafruit_SH1106G display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

void setup() {

  Serial.begin(9600);
  Wire.begin();

  delay(250);

  if (!display.begin(i2c_Address, true)) {
    Serial.println("ERROR: OLED no encontrada");
    while (1);
  }

  display.clearDisplay();
  display.display();
}

void loop() {

  lectura = analogRead(LM35);
  temperatura = (lectura * 5.0 / 1023.0) * 100.0; 

  Serial.println(temperatura);

  display.clearDisplay();

  display.setTextColor(SH110X_WHITE);
  display.setTextSize(1);
  display.setCursor(15, 10);
  display.println("Temperatura:");

  display.setTextSize(2);
  display.setCursor(15, 30);
  display.print(temperatura, 1);  
  display.setTextSize(1);
  display.print(" C");

  display.display();

  delay(1000);
}