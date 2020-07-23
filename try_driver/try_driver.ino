#define PIN_MOTOR_SPEED 5
#define PIN_FORWARD 7
#define PIN_BACKWARD 8
#define PIN_FORWARD_READ 12
#define PIN_BACKWARD_READ 13

void setup() {
  Serial.begin(9600);
  pinMode(PIN_MOTOR_SPEED, OUTPUT);
  pinMode(PIN_FORWARD, OUTPUT);
  pinMode(PIN_BACKWARD, OUTPUT);
  pinMode(PIN_FORWARD_READ, INPUT_PULLUP);
  pinMode(PIN_BACKWARD_READ, INPUT_PULLUP);
}

void loop() {
  if (!digitalRead(PIN_FORWARD_READ)) {
    digitalWrite(PIN_FORWARD, HIGH); 
    digitalWrite(PIN_BACKWARD, LOW); 
    Serial.println("Forward");
  } else if (!digitalRead(PIN_BACKWARD_READ)) {
    digitalWrite(PIN_FORWARD, LOW); 
    digitalWrite(PIN_BACKWARD, HIGH); 
    Serial.println("Backward");
  } else {
    digitalWrite(PIN_FORWARD, LOW); 
    digitalWrite(PIN_BACKWARD, LOW); 
  }
  analogWrite(PIN_MOTOR_SPEED, 255);
  
  delay(1500);
  analogWrite(PIN_MOTOR_SPEED, 0);
  delay(1500);
}
