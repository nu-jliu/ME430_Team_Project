#include <SoftwareSerial.h>

SoftwareSerial serial(7, 8);

void setup() {
    serial.begin(9600);
    Serial.begin(9600);
}

void loop() {
    if (serial.available() > 0) {
        int a = serial.read();
        Serial.println(a);
        serial.println(a);
    }
    // serial.write(3);

    // Serial.println("222");
}