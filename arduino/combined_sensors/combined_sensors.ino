
//sensors

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN 5
#define DHTTYPE DHT11

DHT_Unified dht(DHTPIN, DHTTYPE);

//wifi

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>



#ifndef STASSID
#define STASSID
#define STAPSK  
#endif 



const char* ssid = STASSID;
const char* password = STAPSK;

const char* host = "
const int httpsPort = 8000;
const char* device_id = "AngelNode3";

String server_name = 


void setup() {

  Serial.begin(115200);
  dht.begin();

  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}


void loop() {
  


  sensors_event_t event; 
  
  dht.temperature().getEvent(&event);
  float temperature = event.temperature;
  
  dht.humidity().getEvent(&event);
  float humidity = event.relative_humidity;

  int sensor1Value = analogRead(A0);
  float brightness = 0;
  brightness = (sensor1Value * (3.3 / 1023.0)) / 3.3;

//  Serial.print(temperature);
//  Serial.print(humidity);
//  Serial.println(brightness);


  if (WiFi.status() == WL_CONNECTED)
  {


    String httpData = server_name;
    httpData.concat("?device_id=");
    httpData.concat(device_id);
    httpData.concat("&temp=");
    httpData.concat(temperature);
    httpData.concat("&humid=");
    httpData.concat(humidity);
    httpData.concat("&light=");
    httpData.concat(brightness);
    Serial.println(httpData);
    
    HTTPClient http;
    http.begin(httpData);
    
    int httpResponseCode = http.POST(httpData);

    if (httpResponseCode > 0) { 

    String payload = http.getString();
    Serial.println(httpResponseCode);
    Serial.println(payload);
    }
    else {
    Serial.println("HTTP ERROR");
    http.end();
    }

  delay(5000);
}
}
