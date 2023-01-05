#include <M5Core2.h>

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  M5.Lcd.setTextSize(3);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  M5.Lcd.progressBar(40,80,240,20,20);
  delay(300);
  M5.Lcd.progressBar(40,80,240,20,40);
  delay(300);
  M5.Lcd.progressBar(40,80,240,20,60);
  delay(300);
  M5.Lcd.progressBar(40,80,240,20,80);
  delay(300);
  M5.Lcd.progressBar(40,80,240,20,100);
  M5.Lcd.setCursor(80,120);
  M5.Lcd.printf("Completed!");
  delay(1000);
  M5.Lcd.begin();
  
}
