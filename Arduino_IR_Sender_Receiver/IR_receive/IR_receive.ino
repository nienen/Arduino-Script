#include <IRremote.h> //預先定義好很多 IR 相關的函式

int IR_rec = 2; // 設定 D2 腳位為 IR 接收器

void setup() {
  Serial.begin(115200);
  IrReceiver.begin(IR_rec); // IrReceiver.begin(pin);
}

void loop() {
  if (IrReceiver.decode()) { // 檢查是否收到訊號 // IrReceiver.decode() 有點類似 Serial.available()
    IrReceiver.printIRResultShort(&Serial); // 顯示解碼結果
    if (IrReceiver.decodedIRData.protocol == UNKNOWN) { // IrReceiver.decodedIRData.protocol
      IrReceiver.printIRResultRawFormatted(&Serial, true);
    }else if (IrReceiver.decodedIRData.command == 0x8E){ // 請將 '0x8E' 替換為你紅外線發射器所發射出來的編碼
      Serial.println("You press the '4'!");
    }else if (IrReceiver.decodedIRData.decodedRawData == 0x708FFD01){ // 請將 '0x708FFD01' 替換為你紅外線發射器所發射出來的編碼
      Serial.println("You press the '5'!");
    }
    IrReceiver.resume(); // 繼續接收下一個訊號
  }
}
