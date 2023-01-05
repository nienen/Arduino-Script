int number = 78;

int number2 = 0x45;

void setup() {
  Serial.begin(115200);
  
}

void loop() {
  Serial.println("======");
  Serial.println("This is a new round");
  Serial.println("INT Use print");
  Serial.println(number);
  Serial.println("STR Use print");
  Serial.println("Hello");
  Serial.println("-----");
  Serial.println("INT Use write");
  Serial.print("");
  Serial.write(number);
  Serial.println("");
  Serial.print("STR Use write");
  Serial.println("");
  Serial.write("Hello");
  Serial.println("");
  Serial.write(number2);
  delay(10000);
}
