int led_pin = 13;
int mer_pin = 10;

void setup() {
  Serial.begin(115200); // baud -> 每秒可以傳 115200 bits
  pinMode (led_pin, OUTPUT);
  pinMode (mer_pin, INPUT);
}

void loop() {
  if(digitalRead(mer_pin) == HIGH){
    digitalWrite (led_pin, HIGH);
    Serial.println("HIGH");
  }else{
    digitalWrite (led_pin, LOW);
    Serial.println("LOW");
  }
  delay(500);
}
