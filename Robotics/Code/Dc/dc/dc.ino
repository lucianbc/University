int enablePin = 11;
int in1Pin = 7;
int in2Pin = 6;

int speed = 255;

void setup() {
  // put your setup code here, to run once:
  pinMode(enablePin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  setMotor(speed, 1);
}

void setMotor(int speed, int direction) {
  analogWrite(enablePin, speed);
  digitalWrite(in1Pin, direction);
  digitalWrite(in2Pin, !direction);
}

