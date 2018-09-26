#include <Wire.h>


#define VALUE_A   0xAA
#define VALUE_B   0xBB
#define VALUE_C   0xCC

#define EVENT_A   0
#define EVENT_B   1
#define EVENT_C   2

uint8_t EVENT = 0;

void setup() {
  Wire.begin(33);
  Wire.onRequest(requestEvent); // data request to slave
  Wire.onReceive(receiveEvent); // data slave received
  Serial.begin(9600);
  Serial.println("I2C Slave ready!");
}

void receiveEvent(int countToRead) {
  byte x;
  while (0 < Wire.available()) {
    x = Wire.read();
    Serial.println(x);
  }
  String message = "Receive event: ";
  String out = message + x;
  EVENT = x;
  
  Serial.print("countToRead: ");
  Serial.println(countToRead);
}

void requestEvent() {
  String event_s = "0xFF";
  switch (EVENT) {
    case EVENT_A:
      
      Wire.write(VALUE_A);
      event_s = String(VALUE_A,HEX);
      Serial.println("Request event: " + event_s);
      break;
    case EVENT_B:
      Wire.write(VALUE_B);
      event_s = String(VALUE_B,HEX);
      Serial.println("Request event: " + event_s);
      break;
    case EVENT_C:
      Wire.write(VALUE_C);
      event_s = String(VALUE_C,HEX);
      Serial.println("Request event: " + event_s);
      break;
    default:
      Wire.write(0xFF);
      event_s = String(0xFF,HEX);
      Serial.println("Request event: " + event_s);
      break;
    }
  Serial.println("Request event OUT: " + event_s);
}

void loop() {
  delay(50);
}
