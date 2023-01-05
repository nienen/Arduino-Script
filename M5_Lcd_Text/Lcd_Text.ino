#include <M5Core2.h>

void setup() {
  M5.begin();
  M5.Lcd.setTextSize(3);
  M5.Lcd.setCursor(70,80);
  M5.Lcd.printf("Hello World");
}

void loop() {
}
