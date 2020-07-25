#include <Servo.h>
#include <LiquidCrystal.h>

#define PIN_SERVO_1 3
#define PIN_SERVO_2 5
#define PIN_SERVO_3 6
#define PIN_SERVO_4 9

#define PIN_PUSHBUTTON_1 4
#define PIN_PUSHBUTTON_2 7
#define PIN_PUSHBUTTON_3 8
#define PIN_PUSHBUTTON_4 12

#define PIN_POTENTIOMETER 0

#define PIN_RS 40
#define PIN_EN 38
#define PIN_D4 52
#define PIN_D5 50
#define PIN_D6 48
#define PIN_D7 46

Servo servo_1;
Servo servo_2;
Servo servo_3;
Servo servo_4;

LiquidCrystal lcd(PIN_RS, PIN_EN, PIN_D4, PIN_D5, PIN_D6, PIN_D7);

int degree;

void setup() {
    pinMode(PIN_PUSHBUTTON_1, INPUT_PULLUP);
    pinMode(PIN_PUSHBUTTON_2, INPUT_PULLUP);
    pinMode(PIN_PUSHBUTTON_3, INPUT_PULLUP);
    pinMode(PIN_PUSHBUTTON_4, INPUT_PULLUP);

    servo_1.attach(PIN_SERVO_1);
    servo_2.attach(PIN_SERVO_2);
    servo_3.attach(PIN_SERVO_3);
    servo_4.attach(PIN_SERVO_4);

    Serial.begin(9600);
    lcd.begin(16, 2);
    lcd.clear();
    // lcd.print("Hello World");
}

void loop() {
    degree = map(analogRead(PIN_POTENTIOMETER), 0, 1023, 0, 180);
    if (!digitalRead(PIN_PUSHBUTTON_1)) {
        servo_1.write(degree);
        printSerial(1, degree);
        printLCD("Base", degree);
    } else if (!digitalRead(PIN_PUSHBUTTON_2)) {
        servo_2.write(degree);
        printSerial(2, degree);
        printLCD("Lower Pivot", degree);
    } else if (!digitalRead(PIN_PUSHBUTTON_3)) {
        servo_3.write(degree);
        printSerial(3, degree);
        printLCD("Upper Pivot", degree);
    } else if (!digitalRead(PIN_PUSHBUTTON_4)) {
        servo_4.write(degree);
        printSerial(4, degree);
        printLCD("Craw", degree);
    }
    delay(15);
}

void printSerial(int numServo, int servoDegree) {
    Serial.print("Servo ");
    Serial.print(numServo);
    Serial.print(": ");
    Serial.println(servoDegree);
}

void printLCD(String part, int servoDegree) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(part);
    lcd.setCursor(0, 1);
    lcd.print("Servo: ");
    lcd.print(servoDegree);
}

