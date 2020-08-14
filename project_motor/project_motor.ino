#include <Servo.h>
#include <SoftwareSerial.h>
// #include <PID_v1.h>

#define PIN_SERVO_1 3
#define PIN_SERVO_2 5
#define PIN_SERVO_3 6
#define PIN_SERVO_4 9

#define PIN_FORWARD_MOTOR_1 44
#define PIN_FORWARD_MOTOR_2 50

#define PIN_REVERSE_MOTOR_1 45
#define PIN_REVERSE_MOTOR_2 51

#define PIN_MOTOR_SPEED_1 10
#define PIN_MOTOR_SPEED_2 11

#define PIN_SONAR_ECHO_1 37
#define PIN_SONAR_TRIG_1 36

#define PIN_SONAR_ECHO_2 30
#define PIN_SONAR_TRIG_2 31

Servo myServoTop1;
Servo myServoTop2;
Servo myServoTop3;
Servo myServoTop4;

SoftwareSerial bluetoothSerial(14, 15);

double sonarInput1;
double motorOutput;
double setPoint = 20;

double ki = 3;
double kp = 3;
double kd = 2;

// PID myPid(&sonarInput1, &motorOutput, &setPoint, kp, ki, kd, DIRECT);

void setup() {
    // myServoTop1.attach(PIN_SERVO_1); // top 1
    // myServoTop2.attach(PIN_SERVO_2); // top 2 (3,5,6,9)
    // myServoTop3.attach(PIN_SERVO_3); // top 3
    // myServoTop4.attach(PIN_SERVO_4); // top 4

    pinMode(PIN_FORWARD_MOTOR_1, OUTPUT);
    pinMode(PIN_FORWARD_MOTOR_2, OUTPUT);

    pinMode(PIN_SONAR_TRIG_1, OUTPUT);
    pinMode(PIN_SONAR_ECHO_1, INPUT);

    pinMode(PIN_SONAR_TRIG_2, OUTPUT);
    pinMode(PIN_SONAR_ECHO_2, INPUT);

    Serial.begin(9600);
    bluetoothSerial.begin(9600);

    // reset();
}

void loop() {

    digitalWrite(PIN_FORWARD_MOTOR_1, HIGH);
    digitalWrite(PIN_FORWARD_MOTOR_2, HIGH);

    analogWrite(PIN_MOTOR_SPEED_1, 255);
    analogWrite(PIN_MOTOR_SPEED_2, 255);

    String input = "";

    if (bluetoothSerial.available()) {
        char inputChar = bluetoothSerial.read();
        input = String(inputChar) + "";
        Serial.println(input);
    }

    // hold();

    // if (input.equalsIgnoreCase("1"))
    //     myServoTop1.write(myServoTop1.read() + 10);
    // else if (input.equalsIgnoreCase("2"))
    //     myServoTop1.write(myServoTop2.read() + 10);
    // else if (input.equalsIgnoreCase("3"))
    //     myServoTop1.write(myServoTop3.read() + 10);
    // else if (input.equalsIgnoreCase("4"))
    //     myServoTop1.write(myServoTop4.read() + 10);

    if (input.equalsIgnoreCase("1"))
        reset();
    else if (input.equalsIgnoreCase("2"))
        grab();
    else if (input.equalsIgnoreCase("3"))
        hold();
    else if (input.equalsIgnoreCase("4"))
        put();
    

    // Serial.print("Servo 1: ");
    // Serial.println(myServoTop1.read());
    // Serial.print("Servo 2: ");
    // Serial.println(myServoTop2.read());
    // Serial.print("Servo 3: ");
    // Serial.println(myServoTop3.read());
    // Serial.print("Servo 4: ");
    // Serial.println(myServoTop4.read());

    Serial.print("Distance 1 = ");
    Serial.println(getSonarDistance(
        PIN_SONAR_TRIG_1, 
        PIN_SONAR_ECHO_1
    ));

    Serial.print("Distance 2 = ");
    Serial.println(getSonarDistance(
        PIN_SONAR_TRIG_2, 
        PIN_SONAR_ECHO_2
    ));

}

void reset() {
    myServoTop1.write(180);
    myServoTop2.write(20);
    myServoTop3.write(90);
    myServoTop4.write(145);
}

void grab() {
    myServoTop1.write(120);
    myServoTop2.write(110);
    myServoTop3.write(120);
    myServoTop4.write(145);
}

void hold() {
    myServoTop1.write(180);
    myServoTop2.write(70);
    myServoTop3.write(60);
    myServoTop4.write(145);
}

void put() {
    myServoTop1.write(120);
    myServoTop2.write(70);
    myServoTop3.write(60);
    myServoTop4.write(145);

    delay(1000);

    reset();
}

long getSonarDistance(int trigPin, int echoPin) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(3);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(15);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH);
    long distance = duration * 0.034 / 2;

    return distance;
}                                                                   