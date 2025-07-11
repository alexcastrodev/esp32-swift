#include <Adafruit_NeoPixel.h>
#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT11

#define RGB_PIN 8
#define NUM_PIXELS 1

Adafruit_NeoPixel pixel(NUM_PIXELS, RGB_PIN, NEO_GRB + NEO_KHZ800);
DHT dht(DHTPIN, DHTTYPE);

void light(uint8_t r, uint8_t g, uint8_t b) {
  pixel.setPixelColor(0, pixel.Color(r, g, b));
  pixel.show();
}

void setup() {
  delay(1000);
  Serial.begin(115200);

  pixel.begin();
  pixel.clear();
  pixel.show();

  // 🟢 
  light(0, 255, 0);
  delay(3000);

  Serial.begin(115200);

  // Wait for Serial to be ready
  while (!Serial) {
    ;
  }

  Serial.println("ESP32-C6 Serial working!");
  dht.begin();
}

void loop() {
  
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    // 🔴 
    light(255, 0, 0);
    delay(500);
    return;
  } else {
    // 🔵 
    light(0, 0, 255);
  }

  pixel.clear();
  pixel.show();

  Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.print(" °C | Umidade: ");
  Serial.print(humidity);
  Serial.println(" %");

  delay(2000);
}
