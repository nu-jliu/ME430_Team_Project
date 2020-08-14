#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);

void setup() {
    mySerial.begin(9600);
    Serial.begin(9600);
} 
 
void loop() {
    char i = '0';
    // boolean available = mySerial.available();
    // Serial.println(available);
    if (mySerial.available()) {
        Serial.print("True");
        char j = mySerial.read();
    // }
        // mySerial.print("Hello");
        // if (i != '0')
        // Serial.println(i);
        Serial.println(j);
        mySerial.println(j);
    }
    Serial.println(mySerial.read());
}
