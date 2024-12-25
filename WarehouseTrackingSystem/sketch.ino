#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"
#include <LiquidCrystal.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

// Sunucu URL
const char* serverUrl = "http://nildenizalsan.com.tr/data.xml";

const int ledPin = 2;

LiquidCrystal lcd(16, 17, 18, 19, 21, 22); // RS, E, D4, D5, D6, D7

// DHT sensör ayarları
#define DHTPIN 15 // Sensörün bağlı olduğu pin

#define DHTTYPE DHT22 // DHT sensör tipi (DHT11 veya DHT22 olabilir)
DHT dht(DHTPIN, DHTTYPE);

void setup() {

  lcd.begin(16, 2); // 16x2 LCD için başlatma
  lcd.print("Wi-Fi Baglaniyor"); // Ekranda mesaj göster

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  // WiFi bağlantısı
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("WiFi'ye bağlanılıyor...");
  }
  lcd.clear();
  lcd.print("Wi-Fi baglandi");
  lcd.setCursor(0, 1); // İkinci satıra geç
  lcd.print("IP: " + WiFi.localIP().toString());

  Serial.println("IP Adresi: " + WiFi.localIP().toString());
  Serial.println("WiFi'ye bağlandı!");
  dht.begin();
}

void sendData() {
  float temperature = random(20, 35) + random(0, 99) / 100.0; // 20.00 - 35.99 arasında sıcaklık
  float humidity = random(40, 60) + random(0, 99) / 100.0;    // 40.00 - 60.99 arasında nem

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Sensörden veri okunamadı!");
  } else {
    // XML formatında veri hazırlığı
    String xmlData = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
    xmlData += "<data>";
    xmlData += "<temperature>" + String(temperature) + "</temperature>";
    xmlData += "<humidity>" + String(humidity) + "</humidity>";
    xmlData += "</data>";

    Serial.println("Gönderilen XML Verisi:");
    Serial.println(xmlData);

    // HTTP POST isteği gönder
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/xml");

    int httpResponseCode = http.POST(xmlData);

    if (httpResponseCode > 0) {
      Serial.println("Veri gönderildi!");
      Serial.println("HTTP Yanıt Kodu: " + String(httpResponseCode));
    } else {
      Serial.println("HTTP isteği başarısız oldu!");
      Serial.println("Hata: " + String(http.errorToString(httpResponseCode).c_str()));
    }

    http.end();
  }
}

void fetchData() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);

    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("HTTP Yanıt Kodu: " + String(httpResponseCode));
      Serial.println("Alınan Veri:");
      Serial.println(response);

      lcd.clear();
      lcd.print("Alinan Veri:");
      lcd.setCursor(0, 1);
      lcd.print(response.substring(0, 16)); // LCD için ilk 16 karakter
    } else {
      Serial.println("HTTP isteği başarısız oldu!");
      Serial.println("Hata: " + String(http.errorToString(httpResponseCode).c_str()));
    }

    http.end();
  } else {
    Serial.println("WiFi bağlantısı kaybedildi!");
  }
}

void loop() {
  sendData();
  delay(10000); // Veri gönderme için bekleme
  fetchData();
  delay(10000); // Veri alma için bekleme
}
