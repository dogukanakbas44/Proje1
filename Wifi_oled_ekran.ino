#include <SPI.h>   //Kitaplıklar, ESP8266 Wi-Fi'nin yanı sıra OLED ekranı başlatmak içindir
#include <Wire.h>
#include "ESP8266WiFi.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);  //Bu kod satırı, sürücü tipinin yanı sıra ekranın boyutlarını belirtmek için kullanılır
 
 
void setup() {
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
 
  WiFi.mode(WIFI_STA);   //Bu satırda ESP radyo modunu bir an için İSTASYON MODU'na ayarladık
  WiFi.disconnect();
  delay(100);
 
  Serial.println("Setup done");
 
 
  display.clearDisplay();
  display.display();
}
 
void loop() {
  
  Serial.println("scan start");
 
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0) {
    Serial.println("no networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {   //Bu bölümde, monitör serisindeki SSID ve RSSI değerlerini görüntülüyoruz. RSSI aslında ağın sinyal gücüdür
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
      delay(10);
      
 
  display.setTextColor(SSD1306_WHITE);   //Bu bölümde, OLED ekranda ekranın üst kısmına kullanılabilir WIFI ağlarının toplam sayısını yazdıracağız
  display.setCursor(25,0);
  display.print("Networks: ");
  display.print(n);
 
        
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,8);                //Son olarak, her satıra SSID değerlerini yazdırıyoruz
  display.println(WiFi.SSID(0));
  display.println(WiFi.SSID(1));
  display.println(WiFi.SSID(2));
  display.println(WiFi.SSID(3));
  display.println(WiFi.SSID(4));
  display.setCursor(0,0);
  display.display();
  display.clearDisplay();
      
    }
  }
  Serial.println("");
  delay(50);
}
