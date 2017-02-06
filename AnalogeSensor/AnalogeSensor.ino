#define analogSensorPin 0

int value;

void setup() {
  pinMode(analogSensorPin,OUTPUT);

  value = 0;
  
  Serial.begin(9600);
}

void loop() {
  value = analogRead(analogSensorPin);
  Serial.println(value);
}
