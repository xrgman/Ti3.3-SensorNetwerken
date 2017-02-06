#define switchPin 5

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;

void turnLightOn(int lightID);
void turnLightOff(int lightID);

bool state;

void setup() {
    pinMode(switchPin,INPUT);
    Serial.begin(9600);
 

    for(uint8_t t = 4; t > 0; t--) {
        Serial.printf("[SETUP] WAIT %d...\n", t);
        Serial.flush();
        delay(1000);
    }

    WiFiMulti.addAP("hoi", "daag");
}

void loop() {
    // wait for WiFi connection
    if((WiFiMulti.run() == WL_CONNECTED)) {
      int newState = digitalRead(switchPin);

      if(newState != state) {
      
        if(newState) {
          turnLightOn(1);
        }
        else {
          turnLightOff(1);
        }

        state= newState;
      }
    }
    else
      Serial.println("Failed to connect!");
    delay(100);
}


void turnLightOn(int lightID) {
  HTTPClient http;

  String request = "http://192.168.1.132:8000/api/1502a28be4803a275231925ee1b9a4e/lights/";
  request += lightID;
  request += "/state";
  
  http.begin(request); //HTTP
  int httpCode = http.sendRequest("PUT","{ 'on': true }");

  if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
  }

  http.end();
}

void turnLightOff(int lightID) {
  HTTPClient http;

  String request = "http://192.168.1.132:8000/api/1502a28be4803a275231925ee1b9a4e/lights/";
  request += lightID;
  request += "/state";
  
  http.begin(request); //HTTP
  int httpCode = http.sendRequest("PUT","{ 'on': false }");

  if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
  }

  http.end();
}


