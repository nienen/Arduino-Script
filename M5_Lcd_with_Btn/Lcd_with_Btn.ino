#include <M5Core2.h>

#define myRED 0xe8e4
#define myGREEN 0x2589
#define myBLUE 0x51d

void setup() {
  M5.begin();
  M5.Lcd.setBrightness(100);//螢幕亮度100
  M5.Lcd.setTextSize(3); //字體大小
  
  //
  M5.Lcd.setCursor(44, 215); //設定座標
  M5.Lcd.setTextColor(myRED); //字體顏色：紅
  M5.Lcd.printf("RED");
  M5.Lcd.drawRect(42, 212, 55, 30, myRED); //繪製長方形
  //在 (44,215) 座標上繪製一個 GREEN 的字並且有長方形外框
  
  //
  M5.Lcd.setCursor(116, 215); //設定座標
  M5.Lcd.setTextColor(myGREEN); //字體顏色：綠
  M5.Lcd.printf("GREEN");
  M5.Lcd.drawRect(114, 212, 91, 30, myGREEN); //繪製長方形
  // 在 (116,215) 座標上繪製一個 GREEN 的字並且有長方形外框

  M5.Lcd.setCursor(222, 215);
  M5.Lcd.setTextColor(myBLUE);
  M5.Lcd.printf("BLUE");
  M5.Lcd.drawRect(220, 212, 73, 30, myBLUE);
}

void loop() {
  M5.update();
  if (M5.BtnA.wasPressed()){      //BtnA 被按下
    M5.Lcd.fillCircle(160, 120, 80, myRED); //畫一個紅色的圓
  }
  if (M5.BtnB.wasPressed()){
    M5.Lcd.fillCircle(160, 120, 80, myGREEN);
  }
  if (M5.BtnC.wasPressed()){
    M5.Lcd.fillCircle(160, 120, 80, myBLUE);
  }
}
