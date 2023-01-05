#include <IRremote.h>

uint16_t sAddress = 0x0102; // 這個也要記得改
uint8_t sCommand = 0xC; // 這個才是真正的指令
uint8_t sRepeats = 0; // 訊號發送要重複幾次 （保險機制）
int IR_SEND_PIN = 3;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT); // LED
  IrSender.begin(IR_SEND_PIN, ENABLE_LED_FEEDBACK); // 初始化 IR 發射器
//  Serial.println(IR_SEND_PIN);
}

void loop() {
  Serial.print("Send now: address=0x");
  Serial.print(sAddress, HEX);
  Serial.print(" command=0x");
  Serial.print(sCommand, HEX);
  Serial.print(" repeats=");
  Serial.print(sRepeats);
  Serial.println();
  Serial.println("(Send NEC with 16 bit address)");
  Serial.flush();
  
  IrSender.sendNEC(sAddress, sCommand, sRepeats); // 本程式碼中最重要的一行
  IrSender.sendNECRaw(0xCB340102, sRepeats);
  delay(10000);
}
