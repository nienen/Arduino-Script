// Adafruit
#include <DHT.h>
#include <DHT_U.h>

int dht_pin = 10; // 設定 pin 腳

DHT dht(dht_pin, DHT11); // (腳位, DHT 型號) 
// DHT dht(2, DHT22); <-- 如果你是用 D2 的 DHT22 這個型號的感測器的話


void setup() {
  Serial.begin(115200);
  dht.begin();  // 初始化 DHT lcd.begin(); IrReceiver.begin();
}

void loop() {
  delay(2000); // 延遲 2s
  float h = dht.readHumidity();   //取得濕度
  float t = dht.readTemperature();  //取得溫度(°C)
  float f = dht.readTemperature(true); //取得溫度(°F)
  // isnan(h) h 是否為空值
  // 「&&」 且，「|」 或
  if(isnan(h) | isnan(t) | isnan(f)){
    Serial.println("Failed to read from DHT sensor");
    return;
  }else{
    float hif = dht.computeHeatIndex(f, h); // 利用上述程式所得到的「f」、「h」來計算酷熱指數(°F) 
    float hic = dht.computeHeatIndex(t, h, false); // 利用上述程式所得到的「t」、「h」來計算酷熱指數(°C)
    Serial.println(String("相對濕度: ")+h+String("%"));
    Serial.println(String("溫度: ")+t+String("°C /")+f+String("°F"));
    Serial.println(String("酷熱指數: ")+hic+String("°C / ")+hif+String("°F"));
    Serial.println("======");
  }
}
