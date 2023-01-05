#include <M5Core2.h>

float init_temp = 0.0;
float current_temp = 0.0F;


void setup() {
  
  // Initialize the M5Stack object
  M5.begin();
  M5.IMU.Init();
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.setTextSize(2);

}

void loop() {

  M5.IMU.getTempData(&current_temp);
  M5.Lcd.setCursor(2, 150);
  M5.Lcd.printf("Current Temp : %.2F C", current_temp);

  delay(500);

}
