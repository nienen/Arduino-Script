int hall_pin = 10; // 宣告 D10 為霍爾感測模組腳位       

void setup() {   
  pinMode(hall_pin, INPUT); // D10 「輸入」
  Serial.begin(115200); // 初始化 Serial Port 鮑率 115200
}

void loop(){
  // 沒有偵測到磁鐵的時候 1
  if (digitalRead(hall_pin) == LOW) { // 偵測到磁鐵靠近 感測值變為低電位 
    Serial.println(LOW);      
  }
  else {      
    Serial.println(HIGH);
  }
  delay(1000);  
}
