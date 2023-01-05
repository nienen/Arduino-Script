#include <DHT.h>
#include <DHT_U.h>
int dht_pin = 10; // 設定 pin 腳
DHT dht(dht_pin, DHT11); // （腳位， DHT 型號） 
void setup(){
  Serial.begin(115200);
  dht.begin();  // 初始化 DHT
}
void loop() {
  delay(2000); //延遲2s
  float h = dht.readHumidity();   //取得濕度
  float t = dht.readTemperature();  //取得溫度(°C)
  float f = dht.readTemperature(true); //取得溫度(°F)
  // isnan 為 是否為空值
  if(isnan(h) | isnan(t) | isnan(f)){
    Serial.println("Failed to read from DHT sensor");
    return;
  }else{
    float hif = dht.computeHeatIndex(f, h); // 計算酷熱指數(°F)
    float hic = dht.computeHeatIndex(t, h, false); // 計算酷熱指數(°C)
    Serial.print("{'H':"); Serial.print(h);Serial.print(",");
    Serial.print("'T':"); Serial.print(t);Serial.print(",");
    Serial.print("'HIC':"); Serial.print(hic);Serial.println("}");
  }
}
