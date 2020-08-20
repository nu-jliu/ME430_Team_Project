#include <Servo.h>
#include <SoftwareSerial.h>
#include <PID_v1.h>

/* Servo configuration */
#define PIN_SERVO_1 3
#define PIN_SERVO_2 5
#define PIN_SERVO_3 6
#define PIN_SERVO_4 9

/* Motor direction configuration */
// Forward
#define PIN_FORWARD_MOTOR_1 44
#define PIN_FORWARD_MOTOR_2 50

// Reverse
#define PIN_REVERSE_MOTOR_1 45
#define PIN_REVERSE_MOTOR_2 51

/* Motor Speed Configuration */
#define PIN_MOTOR_SPEED_1 10
#define PIN_MOTOR_SPEED_2 11

/* Sonar Sensor Configuratoin */
#define PIN_SONAR_ECHO_1 37
#define PIN_SONAR_TRIG_1 36

#define PIN_SONAR_ECHO_2 22
#define PIN_SONAR_TRIG_2 23

/* Bluetooth Configuration */
#define PIN_RX 8
#define PIN_TX 7

/* PID Controller Configuration */
#define K_I 6
#define K_P 3
#define K_D 2

Servo myServoTop1;
Servo myServoTop2;
Servo myServoTop3;
Servo myServoTop4;

SoftwareSerial bluetoothSerial(PIN_TX, PIN_RX);

double sonarInput1;
double motorOutput;
double setPoint = 50;

PID myPid(&sonarInput1, &motorOutput, &setPoint, K_P, K_I, K_D, REVERSE);

bool goingForward = true;

void setup() {
    /* Servo setup */
    myServoTop1.attach(PIN_SERVO_1); // top 1
    myServoTop2.attach(PIN_SERVO_2); // top 2 (3,5,6,9)
    myServoTop3.attach(PIN_SERVO_3); // top 3
    myServoTop4.attach(PIN_SERVO_4); // top 4

    /* Motor direction */
    pinMode(PIN_FORWARD_MOTOR_1, OUTPUT);
    pinMode(PIN_FORWARD_MOTOR_2, OUTPUT);
    pinMode(PIN_REVERSE_MOTOR_1, OUTPUT);
    pinMode(PIN_REVERSE_MOTOR_2, OUTPUT);

    /* Sonar sensor */
    pinMode(PIN_SONAR_TRIG_1, OUTPUT);
    pinMode(PIN_SONAR_ECHO_1, INPUT);

    pinMode(PIN_SONAR_TRIG_2, OUTPUT);
    pinMode(PIN_SONAR_ECHO_2, INPUT);

    /* motor speed */
    pinMode(PIN_MOTOR_SPEED_1, OUTPUT);
    pinMode(PIN_MOTOR_SPEED_2, OUTPUT);

    /* bluetooth */
    pinMode(PIN_TX, INPUT);
    pinMode(PIN_RX, OUTPUT);

    Serial.begin(9600);
    bluetoothSerial.begin(9600);

    reset();
}

void loop() {

    forward();

    String input = "";

    if (bluetoothSerial.available() > 0) {
        char inputChar = bluetoothSerial.read();
        input = String(inputChar) + "";
        Serial.println(input);
    }

    if (input.equalsIgnoreCase("1"))
        reset();
    else if (input.equalsIgnoreCase("2"))
        grab();
    else if (input.equalsIgnoreCase("3"))
        hold();
    else if (input.equalsIgnoreCase("4"))
        put();
    else if (input.equalsIgnoreCase("F"))
        forward();
    else if (input.equalsIgnoreCase("R"))
        reverse();
    else if (input.equalsIgnoreCase("L"))
        left();
    else if (input.equalsIgnoreCase("R"))
        right();
    
    // for debug
/*
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
    */

   // pid control
    sonarInput1 = getSonarDistance(
        PIN_SONAR_TRIG_1, 
        PIN_SONAR_ECHO_1
    );
    myPid.SetMode(AUTOMATIC);
    myPid.Compute();

    Serial.print("Distance = ");
    Serial.println(sonarInput1);
    Serial.print("Motor Speed = ");
    Serial.println(motorOutput);

    analogWrite(PIN_MOTOR_SPEED_1, motorOutput);
    analogWrite(PIN_MOTOR_SPEED_2, motorOutput * 3 / 5);
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

    // long duration = pulseIn(echoPin, HIGH);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(50);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH);
    long distance = duration * 0.034 / 2;

    return distance;
}        

void setMotorLeft(bool forward) {
    if (forward) {
        digitalWrite(PIN_REVERSE_MOTOR_1, LOW);
        digitalWrite(PIN_FORWARD_MOTOR_1, HIGH);
    } else {
        digitalWrite(PIN_REVERSE_MOTOR_1, HIGH);
        digitalWrite(PIN_FORWARD_MOTOR_1, LOW);
    }
}

void setMotorRight(bool forward) {
    if (forward) {
        digitalWrite(PIN_REVERSE_MOTOR_2, LOW);
        digitalWrite(PIN_FORWARD_MOTOR_2, HIGH);
    } else {
        digitalWrite(PIN_REVERSE_MOTOR_2, HIGH);
        digitalWrite(PIN_FORWARD_MOTOR_2, LOW);
    }
}

void forward() {
    setMotorLeft(true);
    setMotorRight(true);
}

void reverse() {
    setMotorLeft(false);
    setMotorRight(false);
}

void left() {
    setMotorLeft(false);
    setMotorRight(true);
}

void right() {
    setMotorLeft(true);
    setMotorRight(false);
}