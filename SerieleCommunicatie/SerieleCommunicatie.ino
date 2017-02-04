#include <ESP8266WiFi.h>

void serialEvent();
void processSerialCommand(String cmd);

//RGB pwm values:
int red, green, blue;

//Serial commands:
String cmd;
int cmdIndex;


void setup() {
  //Setting color to white:
  red = 255;
  green = 255;
  blue = 255;
  
  cmdIndex = 0;
  Serial.begin(9600);
}

void loop() {
//  Serial.println("Bliep");
//  delay(1000);

  //Polling the serial commands (Because there is no interrupt :( )
  serialEvent();
}

void serialEvent() {
  if(Serial.available()) {
    char ch = Serial.read();
    cmd += ch;
    //Why moeilijk doen...

    //School way:
    if(ch == '\n' || ch == '\r') {
        cmd[cmdIndex] = '\0';
        cmdIndex = 0;
        processSerialCommand(cmd);
    }
    else {
        cmd[cmdIndex] = ch;
        cmdIndex++;
    }
  }
}

void processSerialCommand(String cmd) {
  Serial.print("Command: ");
  Serial.println(cmd);  
  
  if(cmd.equals("getRGB")) {
    Serial.print("Red: ");
    Serial.println(red);
    Serial.print("Green: ");
    Serial.println(green);
    Serial.print("Blue: ");
    Serial.println(blue);
  }
  else if(cmd.substring(0,7).equals("setRGB:")) {
    red = cmd.substring(7,10).toInt();
    green = cmd.substring(11,14).toInt();
    blue = cmd.substring(15,18).toInt();
  }
  
}

