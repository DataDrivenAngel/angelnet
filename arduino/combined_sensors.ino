
#include <Adafruit_Sensor.h>
#include <DHT.h>

#include <DHT_U.h>
#define DHTPIN 5
#define DHTTYPE DHT11
DHT_Unified dht(DHTPIN, DHTTYPE);


void setup() {

  Serial.begin(9600);
}


void loop() {
  
  int sensor1Value = analogRead(A0);
  dht.begin();
  
  sensors_event_t event; 
  dht.temperature().getEvent(&event);
  
    Serial.print("Temperature: ");
    Serial.print(event.temperature);
    Serial.print(" *C \t");
  

  dht.humidity().getEvent(&event);

    Serial.print("Humidity: ");
    Serial.print(event.relative_humidity);
    Serial.print(" % \t");
  
   float voltage = 0;
   voltage = sensor1Value * (3.3 / 1023.0);

  
  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.print(" V \n");
  
  delay(1000);
}
