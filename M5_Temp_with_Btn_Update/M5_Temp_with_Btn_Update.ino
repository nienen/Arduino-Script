#include <M5Core2.h>

float current_temp = 0.0F;


void setup() {
  
  // Initialize the M5Stack object
  M5.begin();
  M5.IMU.Init();
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(0,80);
  M5.Lcd.println("Use BtnA to update Temp");
  M5.Lcd.println("");
  M5.IMU.getTempData(&current_temp);
  M5.Lcd.setCursor(2, 150);
  M5.Lcd.printf("Current Temp : %.2F C", current_temp);
  
}

void loop() {

  M5.update();
  if(M5.BtnA.wasPressed()){
    M5.IMU.getTempData(&current_temp);
    M5.Lcd.setCursor(2, 150);
    M5.Lcd.printf("Current Temp : %.2F C", current_temp);
  }

}
