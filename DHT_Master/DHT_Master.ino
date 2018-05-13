#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2         // Pin which is connected to the DHT sensor.
#define DHTTYPE DHT22    // DHT 22 (AM2302)
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;
float tcal = 0.01;
float hcal = 0.01;

void setup() {
  Serial.begin(9600);
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;
}

void loop() {
  delay(delayMS);
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    //Serial.println("Error reading temperature!");
  }
  else {
    Serial.print(event.temperature + tcal);
    Serial.print(",");
  }
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    //Serial.println("Error reading humidity!");
  }
  else {
    Serial.print(event.relative_humidity + hcal);
    Serial.print("\n");
  }
}
