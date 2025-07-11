#include <HomeSpan.h>
#include <DHT.h>
#include <Adafruit_NeoPixel.h>
#include <WiFi.h>

// ------------------- CONFIGURATION -------------------

#define DHTPIN 4
#define DHTTYPE DHT11

#define RGB_PIN 8
#define NUM_PIXELS 1

const char* ssid = "";
const char* password = "";

// ------------------- OBJECTS -------------------------

DHT dht(DHTPIN, DHTTYPE);
Adafruit_NeoPixel pixel(NUM_PIXELS, RGB_PIN, NEO_GRB + NEO_KHZ800);

// ------------------- RGB HELPER ----------------------

void setRGB(uint8_t r, uint8_t g, uint8_t b) {
  pixel.setPixelColor(0, pixel.Color(r, g, b));
  pixel.show();
}

// ------------------- HOMESPAN SERVICES ----------------

float temperature = 0.0;
float humidity = 0.0;

struct TemperatureSensorService : Service::TemperatureSensor {
  SpanCharacteristic *temperatureChar;

  TemperatureSensorService() {
    temperatureChar = new Characteristic::CurrentTemperature(20);
    temperatureChar->setRange(-40, 100);
  }

  void loop() override {
    float t = dht.readTemperature();
    if (!isnan(t)) {
      temperature = t;
      temperatureChar->setVal(temperature);
    }
  }
};

struct HumiditySensorService : Service::HumiditySensor {
  SpanCharacteristic *humidityChar;

  HumiditySensorService() {
    humidityChar = new Characteristic::CurrentRelativeHumidity(50);
  }

  void loop() override {
    float h = dht.readHumidity();
    if (!isnan(h)) {
      humidity = h;
      humidityChar->setVal(humidity);
    }
  }
};

// ------------------- SETUP ---------------------------

void setup() {
  Serial.begin(115200);
  delay(1000);

  dht.begin();
  pixel.begin();
  pixel.clear();
  pixel.show();

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    // 🟡
    setRGB(255, 255, 0);
    delay(3000);
  }

  homeSpan.setPairingCode("");
  homeSpan.begin(Category::Sensors, "Sensor Temperatura");

  new SpanAccessory();
    new Service::AccessoryInformation();
      new Characteristic::Name("Room Sensor");
      new Characteristic::Manufacturer("Alex");
      new Characteristic::SerialNumber("DHT001");
      new Characteristic::Model("DHT11");
      new Characteristic::FirmwareRevision("1.0");
      new Characteristic::Identify();

    new TemperatureSensorService();
    new HumiditySensorService();

  // 🟢 Green LED at the end of setup
  setRGB(0, 255, 0);
}

// ------------------- LOOP ----------------------------

void loop() {
  // 🔵 Blue LED during loop
  setRGB(0, 0, 255);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    // 🔴 Red LED on error
    setRGB(255, 0, 0);
    delay(1000);
    return;
  }

  homeSpan.poll();

  delay(1000);
}
