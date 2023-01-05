int red_pin = 11;
int yel_pin = 10;
int val = 0; // 類比

void setup() {
  Serial.begin(9600);
  pinMode(red_pin, OUTPUT);
  pinMode(yel_pin, OUTPUT);
}

void loop() {
  // 第二次這邊 Serial 已經被我 End 掉了
  // 以 255 為起點，只要 val>0 的情況下，我每執行一次迴圈 val 都會 -1
  for(val=255; val>0; val--){
    analogWrite(yel_pin, val); // 寫入 D10 類比訊號 (255->254->253....->0)
    Serial.println(val, DEC); // 印出來目前的 RGB 是多少（十進制表示）
    delay(30); // 延遲 0.3s
  }
//========我是分隔線===========
  // 以 0 為起點，只要 val<255 的情況下，我每執行一次迴圈 val 都會 +1
  for(val=0; val<255; val++){
    analogWrite(red_pin, val);
    Serial.println(val, DEC);
    delay(30);
  }
  digitalWrite(yel_pin, LOW);
  digitalWrite(red_pin, LOW);
}
