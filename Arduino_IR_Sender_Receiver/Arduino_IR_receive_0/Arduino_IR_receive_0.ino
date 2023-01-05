#include <IRremote.h>

int IR_rec = 2; // IR Receiver 腳位: digital pin 2

void setup() {
  Serial.begin(115200);
  IrReceiver.begin(IR_rec);
}

void loop() {
  if (IrReceiver.decode()) { // 檢查是否收到訊號
    IrReceiver.printIRResultShort(&Serial); // 顯示解碼結果
    if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
      IrReceiver.printIRResultRawFormatted(&Serial, true);
    }
    IrReceiver.resume(); // 繼續接收下一個訊號
  }
}
