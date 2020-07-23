#include <SoftwareSerial.h>
#include <Servo.h>
#include <LiquidCrystal.h>

#define PIN_LED 13
#define PIN_SERVO 9
#define PIN_RS 12
#define PIN_EN 11
#define PIN_D4 7
#define PIN_D5 6
#define PIN_D6 5
#define PIN_D7 4

Servo myServo;
SoftwareSerial mySerial(2, 3);
LiquidCrystal lcd(PIN_RS, PIN_EN, PIN_D4, PIN_D5, PIN_D6, PIN_D7);

void setup() {
    mySerial.begin(9600);
    Serial.begin(9600);
    myServo.attach(PIN_SERVO);
    lcd.begin(16, 2);
}

void loop() {
    int i;
    if (mySerial.available()) {
        i = mySerial.read();
        if (i == '1') {
            digitalWrite(PIN_LED, HIGH);
            myServo.write(180);
            lcd.clear();
            lcd.print("Input: HIGH");
            lcd.setCursor(0, 1);
            lcd.print("Servo 180");
        } else if (i == '0') {
            digitalWrite(PIN_LED, LOW);
            myServo.write(0);
            lcd.clear();
            lcd.print("Input: LOW");
            lcd.setCursor(0, 1);
            lcd.print("Servo 0");
        }
        lcd.display();
    }
}