int sound_pin = A0;

void setup() {
  Serial.begin(9600);
  pinMode(sound_pin, INPUT);
}

void loop() {
  int sound_value = analogRead(sound_pin);
  Serial.print("sound vlaue: "); Serial.println(sound_value);
  delay(1000);
}
