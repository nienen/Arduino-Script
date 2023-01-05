# Arduino UNO Basic Intro

## Arduino UNO 腳位細節

| 功能        	| 腳位                                              	| 介紹                                                                                                                                                                                   	|
|-------------	|---------------------------------------------------	|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------	|
| Serial 通訊腳位 	| D0（`RX`）、D1 （`TX`）                                   	| 用來接收（`RX`）與傳輸（`TX`） 訊號，如果是使用電腦（USB） 與 Arduino 進行數據傳輸，應避免使用此腳位。         	|
|   外部中斷    	| D2、D3                                            	| 這兩支腳可以利用外部事件觸發中斷。詳細內容請參考 `attachInterrupt()` 函式。                                                                                                           	|
| PWM（Pulse Width Modulation）         	| D3、D5、D6、D9、D10、D11                      	| 可看見這些腳位旁有波浪符號 `~`。透過 `analogWrite()` 函式用數位訊號來模擬類比訊號輸出，提供 8-bit 的 PWM。                                           	|
| SPI         	| D10 (SS)、D11(MOSI)、D12(MISO)、D13(SCK) 	| 這四支腳搭配 SPI Library 可提供 SPI 序列通訊。                                                                                                                                     	|
| LED         	| D13                                               	| 若是原廠控制板，預設會燒錄一個讓 `D13` 定時切換高低電位的 Blink 程式，因此，首次接上電源時，會看到開發板上標示為 L 的 LED 不斷閃爍，這是初步檢視控制板是否功能正常的方式。 	|
| I2C         	| A4(SDA)、A5(SCL)                                	| 透過 Wire library 可以提供 I2C 通訊。                                                                                                                                              	|
| AREF        	| AREF                                              	| 類比輸入的參考電壓，搭配 `analogReference()` 函式一起使用。                                                                                                                            	|
| Reset       	| Reset                                             	| 按下重置鈕會使開發板重新執行使用者寫入之程式。當 Reset 腳位 LOW 時，功能如同按下重置鈕。 


### Arduino 常用的函式

#### pinMode()

`pinMode()` 函式用來 __設定該腳位為輸入或輸出__，讓透過 pin 腳數字去指定要使用哪一個腳位，還有設定腳位模式（INPUT、OUTPUT），當設定為輸入時，腳位可以偵測感測器傳入的狀態，像是按下按鈕；如果設定為輸出，則可以驅動制動器，像是 LED 燈。

語法： `pinMode(pin, mode)`

> pin: 要設置的 pin 腳數字。 </br>
> mode: `INPUT`、`OUTPUT`

範例：

```C
int led_pin = 13; //設定 LED 於 pin 13

void setup() {
  pinMode(led_pin, OUTPUT); //宣告 pin 13 為輸出腳位
}
```

#### digitalWrite() / digitalRead()

這兩個函式為 __寫入/讀取指定 pin 腳的數位訊號（`HIGH`、`LOW`）__，可用的數位腳位數量會取決於 Arduino 板的種類。

> 由於數位訊號只由 0 與 1 所組成，上述的 `HIGH` 為 `1`；`LOW` 為 `0`。

語法： `digitalWrite(pin)`、`digitalRead(pin)`

> pin: 要設置的 pin 腳數字。

範例：

```C
int led_pin = 13; //設定 LED 於 pin 13

void setup() {
  pinMode(led_pin, OUTPUT); //宣告 pin 13 為輸出腳位
}
void loop() {
  digitalWrite(led_pin, HIGH); //對 pin 13 寫入數位訊號 1
}
```

#### analogRead() / analogWrite()

此函式可從指定的 __類比腳位讀取、寫入值__，可用的類比腳位數量會取決於
 Arduino 板的種類。

|          開發板          	 |    執行電壓  	| 可用類比腳位 	|
|:-----------------------:	|:-----------:|:-----------:	|
| Uno                     	| 5V           	| A0 to A5    |
| Mini, Nano              	| 5V           	| A0 to A7    |
| Mega, Mega2560, MegaADK 	| 5V          	| A0 to A14   |
| Micro                   	| 5V           	| A0 to A11  	|
| Leonardo                	| 5V           	| A0 to A11  	|
| Zero                    	| 3.3V         	| A0 to A5    |
| Due                     	| 3.3V         	| A0 to A11   |
| MKR Family boards       	| 3.3V         	| A0 to A6    |

> 資料來源：[Arduino 文件](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/)

> 類比訊號是由輸入電壓（5V 或 3.3V）轉換為 0 到 1023 之間的整數數值，相對於數位訊號（0 與 1）來說，對於需要精確數值的感測來說，類比訊號會比數位訊號適合。

語法： `analogRead(pin)`、`analogWrite(pin)`

範例：

```C
int analogPin = A3; // potentiometer wiper (middle terminal) connected to analog pin 3

// outside leads to ground and +5V
int val = 0;  // variable to store the value read

void setup() {
  Serial.begin(9600);           //  setup serial
}

void loop() {
  val = analogRead(analogPin);  // read the input pin
  Serial.println(val);          // debug value
}
```

#### analogReference()

還記得我們上述有使用了 `analogRead()` 函式來獲得感測器的電流電壓， 從 `analogRead()` 傳回的值會將介於 `0` 和 `1023` 之間，其中 `0` 代表 `0V`；`1023` 代表 Arduino 板目前的工作電壓。

假設 Arduino 目前的工作電壓為 `5V`，代表 `analogRead()` 所回傳的每個值為 `0.00488V`（5V/1024）。問題就來了，若我們想要測量的是 `0V~2V` 或者 `0V~4.6V` 之間的電壓怎麼辦？

這也是為什麼會有 `AREF（Analogue REFerence）` 這個腳位存在的目的，它允許我們從 `外部電源` 替 Arduino 提供參考電壓，所以假設想要測量最大電壓範圍為 `3.3V` 的話，我們就可以在 AREF 腳位接上一個 `3.3V` 電壓的電源輸入，並透過 `analogReference()` 告訴 Arduino 要以此電壓（`3.3V`）作為依據，如此一來透過 `analogRead()` 讀取出來的每個值就會是 `0.00322V`（3.3V/1024）。

語法：`analogReference(type)`

`type` 有以下幾個參數可帶入：
- __DEFAULT：__ Arduino 板上的預設值（`5V` 或 `3.3V`，會根據 Arduino 板類型而不同）
- __INTERNAL：__ 內建電壓（`ATmega168` 或 `ATmega328P` 上是 `1.1V`；`ATmega32U4` 和 `ATmega8` 上是 `2.56V`，會根據 Arduino 板類型而不同），此參數不適用於 Arduino Mega 板
- __INTERNAL1V1：__ Arduino Mega 專用 `1.1V`
- __INTERNAL2V56：__ Arduino Mega 專用 `2.56V`
- __EXTERNAL：__ `AREF` 腳位的輸入電壓（`0V~5V`）

要特別注意：

- 不要使用低於 `0V` 或高於 `5V` 的電壓作為 `AREF` 腳位上的外部參考電壓。
- 如果在 `AREF` 腳位上使用外部參考電壓，必須將 `analogRead()` 的參數設為 `EXTERNAL`，否則會將有效參考電壓（內部生成）和 `AREF` 腳位電壓相衝突造成短路，導致 Arduino 板上的微控制器損壞。

#### delay()

`delay()` 會暫時停止執行程式碼一段時間（以毫秒為單位）。

語法： `delay(ms)`

> ms: 暫停的毫秒數，一秒鐘有 1000 毫秒。

範例：

```C
int led_pin = 13; //設定 LED 於 pin 13

void setup() {
  pinMode(led_pin, OUTPUT); //宣告 pin 13 為輸出腳位
}
void loop() {
  delay(5000); // 暫停 5s 後才往後執行
  digitalWrite(led_pin, HIGH); //對 pin 13 寫入數位訊號 1
}
```

<!-- ### 小試身手

請透過上述函式撰寫一個 __Arduino pin 13 上內建 LED 燈以每 2s 為頻率閃爍的應用__。

__解答：__

```C
int led_pin = 13;

void setup() {
  pinMode(led_pin, OUTPUT);
}

void loop() {
  digitalWrite(led_pin, HIGH);
  delay(2000);
  digitalWrite(led_pin, LOW);
  delay(2000);
}
``` -->

這個範例程式碼是 Arduino 初學者學習撰寫程式的必經之路，相信大家在完成這個簡單的應用後，對整個 Arduino 的開發已經有了最基礎的概念，在這邊和大家分享一個實用的語法： `LED_BUILTIN`，這是一個 Arduino 內建的 LED 變數（已經將 Arduino 板上內建的 LED 為 pin 13 宣告好），讓開發者在做測試的時候，可以透過此變數快速的宣告 Arduino 內建的 LED。

嘗試修改原先的程式碼，如下圖：

```C
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(2000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(2000);
}
```

會發現透過此參數能更快的宣告並使用 pin 13 這個 Arduino 上內建的 LED，而無需額外宣告。

### Serial

`Serial` 系列函式皆用於 Arduino 和電腦或其他設備之間的通訊，每個 Arduino 至少都有一個 __Serial Port__（中文譯作：__串行端口__，也稱為 UART 或 USART），端口數量會取決於 Arduino 種類而定，如下圖：

|         開發板種類        	|           名稱           	|          SERIAL 腳位          	|  SERIAL1 腳位  	|    SERIAL2 腳位   	|  SERIAL3 腳位  	|
|:--------------------:	|:--------------------------------:	|:-----------------------------:	|:--------------:	|:-----------------:	|:--------------:	|
| Uno, Nano, Mini      	|                                  	| 0(RX), 1(TX)                  	|                	|                   	|                	|
| Mega                 	|                                  	| 0(RX), 1(TX)                  	| 19(RX), 18(TX) 	| 17(RX), 16(TX)    	| 15(RX), 14(TX) 	|
| Leonardo, Micro, Yún 	| Serial                           	|                               	| 0(RX), 1(TX)   	|                   	|                	|
| Uno WiFi Rev.2       	|                                  	| Connected to USB              	| 0(RX), 1(TX)   	| Connected to NINA 	|                	|
| MKR boards           	| Serial                           	|                               	| 13(RX), 14(TX) 	|                   	|                	|
| Zero                 	| SerialUSB (Native USB Port only) 	| Connected to Programming Port 	| 0(RX), 1(TX)   	|                   	|                	|
| Due                  	| SerialUSB (Native USB Port only) 	| 0(RX), 1(TX)                  	| 19(RX), 18(TX) 	| 17(RX), 16(TX)    	| 15(RX), 14(TX) 	|
| 101                  	| Serial                           	|                               	| 0(RX), 1(TX)   	|                   	|                	|

> 資料來源：[Arduino 文件](https://www.arduino.cc/reference/en/language/functions/communication/serial/)

在 Uno、Nano、Mini 和 Mega 等類型的 Arduino 板上，`D0` 和 `D1` 都用於與電腦通訊（燒錄），若有其他東西連接到這些 pin 腳都會干擾通訊，導致無法燒錄程式至板子上，所以通常 `D0` 和 `D1` 我們都不會接感測器。

開發者若想檢視 Arduino 與感測器之間的通訊是否有正常運作，可以使用 Arduino IDE 內建的串行監視器來監視 Arduino 板通訊狀況，只要點擊 IDE 中右上角的 __放大鏡圖示__，並選擇程式碼中所設定的 `鮑率` 便可進行監控。

> 在電子通訊領域，鮑（Baud）即調變速率，指的是單位時間內載波調變狀態變化的次數，是對符號傳輸速率的一種度量衡：1 鮑即指每秒傳輸 1 個符號，而透過不同的調變方式，可以在一個碼元符號上負載多個 bit 訊號。

>「鮑」（Baud）本身已是速率，所以不需要寫成 Baud Rate（Rate 是贅字），這一單位是以法國電訊工程師埃米爾·博多（1845-1903）的姓氏來命名的。

![](./images/monitor.jpg)

__問題就來了，我們該如何設定與確認 `鮑率` 呢？__

#### Serial.begin()

此函式用來 __設置串行數據傳輸速率（以鮑率為單位）__，若要使用 __串行監視器__ 查看通訊的話，請使用右下角選單中的鮑率。

![](./images/Baud.png)

語法： `Serial.begin(speed)`

範例：

```C
void setup() {
  Serial.begin(115200); 
  //打開 serial port 並設定資料傳輸速率為 9600 bps
}

void loop() {

}
```

> 如果程式碼中設定的鮑率與串行監視器所監視的鮑率不同的話，會看不到通訊數據。

#### if(Serial)

此函式用來 __確認指定的串行端口是否準備就緒__，如果此串行端口可用，則會不斷回傳 `true`。

語法：`if(Serial)`

範例：

```C
void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; 
    // wait for serial port to connect
  }
}

void loop() {

}
```

#### Serial.available()

此函式用於 __獲得串行端口中可讀取得數據量__，這些數據是已經儲存在 buffer（可保存 64 bytes） 中的數據。

語法： `Serial.available()`

範例：

```C
int incomingByte = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC); //以十進制形式輸出 incomingByte
  }
}
```

在此範例程式碼中，我們首先將鮑率設定為 `9600`，並在 `loop()` 函式中寫了一個條件判斷式：「倘若 __串行端口中有數據（>0）__，便將數據值讀出並以十進位顯示。」，其中我們透過 `Serial.available()` 來判斷是否有數據，並透過 `Serial.read()` 讀取 buffer 中的數值。

#### Serial.read()

此函式可 __讀取串行端口中的數據__。

語法： `Serial.read()`

#### Serial.write()

此函式可 __將數據寫入串行端口中__。

語法： `Serial.write(val)`、`Serial.write(str)`、`Serial.write(buf, len)`

> val：欲寫入串行端口的值。 </br>
> str：欲寫入串行端口的字串。 </br>
> buf：欲寫入串行端口的數據大小。 </br>
> len：欲寫入的數據長度。 </br>

範例：

```C
void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.write(45); // send a byte with the value 45

  int bytesSent = Serial.write("hello");  
  // send the string "hello"
}
```

這邊要比較注意的是，若是使用 Arduino IDE 1.0 以後的版本，串行傳輸是 __異步__ 的，換言之如果 buffer 中有足夠的空間，`Serial.write()` 是可以順利寫入 buffer 的；但如果 buffer 已滿，`Serial.write()` 則會阻塞，直到 buffer 中有足夠空間，這可能會導致草稿碼運作時出問題。 所以為了避免阻塞狀況發生，可以先使用 `availableForWrite()` 檢查 buffer 中的可用空間（有可用空間則會回傳 `true`）。

#### Serial.print() / Serial.println()

此函式可 __將數據顯示為人類可讀的 ASCII 編碼於串行端口__，比較需要注意的是若要顯示 `浮點數`，預設只會顯示到小數點後兩位，其餘型態則無特殊改動。

__以上兩種用法僅差在 `Serial.println()` 會自動換行；`Serial.print()` 則不會自動換行。__

語法：`Serial.print(val, format)`、`Serial.println(val, format)`

> val: 欲顯示的數值 </br>
> format: 此參數可以 __設定顯示數值的格式__，可用參數：`BIN(二進位)`、`OCT(八進位)`、`DEC(十進位)`、`HEX(十六進位)`；若是 `浮點數` 的話則可以設定欲顯示的小數點位數，例如：`2`、`4`（細節如下範例）。

範例：

```C
void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println('12.1234'); // 12.12
  Serial.println('12'); // 12
  Serial.println('N'); // N
  Serial.println("Hello world."); // Hello world.
  Serial.println(78, BIN); // 1001110
  Serial.println(78, OCT); // 116
  Serial.println(78, DEC); // 78
  Serial.println(78, HEX); // 4E
  Serial.println(1.23456, 0); // 1
  Serial.println(1.23456, 2); // 1.23
}
```

#### Serial.end()

此函式用來 __禁用串行通訊__，若要重新啟用串行通訊的話，請重新使用 `Serial.begin()`。

語法： `Serial.end()`

範例：

```C
void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println('12.1234'); // 12.12
  Serial.println('12'); // 12
  Serial.println('N'); // N
  Serial.println("Hello world."); // Hello world.
  Serial.println(78, BIN); // 1001110
  Serial.println(78, OCT); // 116
  Serial.println(78, DEC); // 78
  Serial.println(78, HEX); // 4E
  Serial.println(1.23456, 0); // 1
  Serial.println(1.23456, 2); // 1.23
  Serial.end();
  Serial.println("Serial is ended"); 
  // You can't see this message due to the serial is ended.
}
```

#### SoftwareSerial 程式庫

上述有提到 Arduino UNO 板的 `D0` 與 `D1` 為 `TX` 與 `RX`，代表電腦與 Arduino 之間的溝通都會透過這兩個腳位完成，所以我們會建議所有的感測器都不要接在 `D0` 與 `D1` 腳位上。

但問題就來了，__倘若我們在實作上需要多個串行端口（Serial Port）怎麼辦？__

若是 Uno、Nano、Mini 這幾種類型板子都只有一組串行端口，若是想要額外有串行端口的話其實很苦惱，這時候就可以透過 __SoftwareSerial__ 程式庫來解決。

這套程式庫無需特別下載，為 Arduino IDE 中內建的程式庫，只需要透過 `#include <SoftwareSerial.h>` 便可以匯入草稿碼中。

```C
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Native USB only
  }
  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(38400);
  mySerial.println("Hello, world?");
}

void loop() {
  if (mySerial.available()){
    Serial.write(mySerial.read());
  }else if (Serial.available()){
    mySerial.write(Serial.read());
  } 
}
```

<!-- ### 小試身手

請撰寫一個以每 2s 為頻率閃爍的 LED，並在 LED 閃爍時同步於串行端口顯示 `Blink`、`Unblink`。

__解答：__

```C
void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("Blink");
  delay(2000);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("Unblink");
  delay(2000);
}
``` -->

### Serial.write() 與 Serial.print() 的差異

基本上所有發送出去的數據都是 `1` 和 `0`，而這 __兩個函式最大的差異在於發送的實際內容是如何轉譯為 `1` 和 `0` 的__，其中最明顯的例子是涉及傳輸數字的情況。

假設現在我們要發送數字 `217`，這個數字的二進制（1 和 0）為 `11011001`，當我們使用 `Serial.write(217)` 時，實際上只是在發送 `11011001`，相同數字作為十六進製表示是 `0xD9`，倘若我們一樣透過 `Serial.write(0xD9)` 則會發送同樣的東西: `11011001`。

好問題來了，假設我們今天是使用 `Serial.write("217")` 時，會發現我們會得到 `00110010 00110001 00110111`，為何會有這個結果呢？ 主要是因為 __當一個「字串」在進行發送時，它會被以每個「字元」拆開，以二進制的方式發送__，所以如果我們使用以下程式碼會發現有一樣的結果：

```C
  Serial.write(50); // 00110010
  Serial.write(51); // 00110001
  Serial.write(55); // 00110111
```


現在讓我們來看看 `Serial.print()`，使用 `Serial.print(217)` 或者 `Serial.print("217")` 會發現顯示的內容都相同（`00110010 00110001 00110111`），這是因為 `print()` 會將任何數值轉換為「字串」再轉換為 ASCII。

懶人包就是：當使用 `write()` 時，發送的是 `二進制數據（binary）`，因此在串口監視器中我們看到的是以 binary 轉換為 ASCII 所對應的值。

而 `print()` 發送數據時，並不是發送 binary，而是會以 String 轉成 ASCII 碼發送，因此串口監視器接收到的是 ASCII 碼，並會直接顯示對應的字串。

```C
int number = 78;

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
  delay(10000);
}
```