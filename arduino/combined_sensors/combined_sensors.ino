
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

const char* host = "192.168.1.255";
const int httpsPort = 443;
const char* device_id = "AngelNode1";

String server_name = "192.168.1.255:443";



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
  Serial.print(server_name);

  // Use WiFiClientSecure class to create TLS connection
  WiFiClientSecure client;
  Serial.print("connecting to ");
  Serial.println(host);

  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return; 
    
  }

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

  //Serial.print(temperature);
  //Serial.print(humidity);
  //Serial.println(brightness);


  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;
    http.begin(server_name);

    http.addHeader("/data_ingest","application/x-www-form-urlencoded");
    String httpData = "device_id=";
    httpData.concat(
      device_id);
    httpData.concat("&dht_temp=");
    httpData.concat(temperature);
    httpData.concat("&dht_hmdty=");
    httpData.concat(humidity);
    httpData.concat("&light=");
    httpData.concat(brightness);
    Serial.println(httpData);
    
   
    
    int httpResponseCode = http.POST(httpData);
    Serial.print("Posted:");
    Serial.println(httpResponseCode);
    http.end();
  }
  
  delay(5000);
}
