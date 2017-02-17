#define rxPin 5
#define txPin 4

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>

ESP8266WiFiMulti WiFiMulti;

SoftwareSerial zigbee(rxPin, txPin);

void sendRandomNumber(int number);
void handleSerialCommand(char letter);

String serialCmd;

void setup() {
    Serial.begin(57600);
    zigbee.begin(9600);
 
    for(uint8_t t = 4; t > 0; t--) {
        //Serial.printf("[SETUP] WAIT %d...\n", t);
        //Serial.flush();
        delay(1000);
    }

    WiFiMulti.addAP("zooi", "daag");
}

void loop() {
    // wait for WiFi connection
    if((WiFiMulti.run() == WL_CONNECTED)) {

      //Receive communication from router zigbee:
      if(zigbee.available()) {
        char letter = zigbee.read();
        Serial.write(letter);
        handleSerialCommand(letter);
      }          
    }
}

void handleSerialCommand(char letter) {
  if(letter != '\n' && letter != '\r') {
    serialCmd += letter;
  }
  else if(serialCmd.length() > 0) {
    int number = serialCmd.toInt();
    sendRandomNumber(number);
    serialCmd = "";
  }
}

void sendRandomNumber(int number) {
  HTTPClient http;
  String request = "http://192.168.1.132:8080/apiv2/random";
  String body = "{ \"Number\": ";
  body += number;
  body += " }";
  
  http.begin(request); //HTTP
  http.addHeader("Content-Type", "application/json;charset=utf-8");
  http.addHeader("cache-control", "no-cache");
            
  int httpCode = http.sendRequest("PUT", body);

  Serial.printf("[HTTP] GET... code: %d\n", httpCode);
  
  if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
  }
  else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
}



