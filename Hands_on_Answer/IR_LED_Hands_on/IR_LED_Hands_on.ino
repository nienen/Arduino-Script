#include <IRremote.h>

int yel_pin = 10;
int red_pin = 11;
int IR_rec = 2;
uint8_t sCommand_yel = 0x8E;
uint8_t sCommand_red = 0x8F;

void setup() {
  Serial.begin(115200);
  pinMode(yel_pin, OUTPUT);
  pinMode(red_pin, OUTPUT);
  IrReceiver.begin(IR_rec);
}

void loop() {
  if(IrReceiver.decode()){
    IrReceiver.printIRResultShort(&Serial);
    if(IrReceiver.decodedIRData.command == sCommand_yel){
      Serial.println("Yellow LED UP");
      digitalWrite(yel_pin, HIGH);
      digitalWrite(red_pin, LOW);
    }else if(IrReceiver.decodedIRData.command == sCommand_red){
      Serial.println("Red LED UP");
      digitalWrite(red_pin, HIGH);
      digitalWrite(yel_pin, LOW);
     }
    IrReceiver.resume();
  }
}
