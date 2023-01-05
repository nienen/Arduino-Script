#include <M5Core2.h>

void setup() {
  M5.begin();
}

void loop() {

  M5.Lcd.qrcode("https://elearning.ecloudture.com",50,10,220,10);
  delay(1000000);

}
