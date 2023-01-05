int relay = 10;

void setup() {
  // put your setup code here, to run once:
  pinMode(relay, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(relay, HIGH);
  Serial.println("亮");
  delay(2000);
  digitalWrite(relay, LOW);
  Serial.println("不亮");
  delay(2000);
}
