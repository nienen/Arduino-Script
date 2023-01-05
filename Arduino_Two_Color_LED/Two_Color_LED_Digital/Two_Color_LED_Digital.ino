int yel_pin = 10;
int red_pin = 11;
void setup(){
  Serial.begin(9600); 
  pinMode(yel_pin, OUTPUT);
  pinMode(red_pin, OUTPUT);
}
void loop(){
 Serial.println("==========");
  //no color
  digitalWrite(yel_pin, LOW);//D10 寫入低電壓 0
  digitalWrite(red_pin, LOW);//D11 寫入低電壓 0
  Serial.println("No Color");//印出"No Color"
  delay(1000);
  
  // yellow
  digitalWrite(yel_pin, HIGH);//D1- 寫入高電壓 1
  digitalWrite(red_pin, LOW);
  Serial.println("黃色燈亮");
  delay(1000); //等待1000毫秒
  
  // red
  digitalWrite(yel_pin, LOW);
  digitalWrite(red_pin, HIGH);
  Serial.println("紅色燈亮");
  delay(1000); //等待1000毫秒
 
  // orange
  digitalWrite(yel_pin, HIGH);
  digitalWrite(red_pin, HIGH);
  Serial.println("黃紅燈亮(橘？)");
  delay(1000);
}
