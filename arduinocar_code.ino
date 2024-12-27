#include <Servo.h>
// #include <Wire.h>
// #include <MPU6050.h>

// Ultrasonic 1 with Servo
#define TRIG_PIN_BAWAH 7
#define ECHO_PIN_BAWAH 8

// Ultrasonic 2
#define TRIG_PIN_ATAS A0
#define ECHO_PIN_ATAS A1

// Motor Driver (L298N)
#define IN1 3
#define IN2 4
#define IN3 5
#define IN4 6

// Servo
#define SERVO_PIN 9
Servo myServo;

// // MPU6050
// MPU6050 mpu;

long duration;
int distance_bawah;
int distance_atas;

int getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveForward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void setup() {
  pinMode(TRIG_PIN_BAWAH, OUTPUT);
  pinMode(ECHO_PIN_BAWAH, INPUT);
  pinMode(TRIG_PIN_ATAS, OUTPUT);
  pinMode(ECHO_PIN_ATAS, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  myServo.attach(SERVO_PIN);
  myServo.write(90); // Servo Default Position

  // Wire.begin();
  // mpu.initialize();

  Serial.begin(9600);
}

void loop() {
  distance_bawah = getDistance(TRIG_PIN_BAWAH, ECHO_PIN_BAWAH);
  Serial.print("Jarak Bawah: ");
  Serial.println(distance_bawah);

  distance_atas = getDistance(TRIG_PIN_ATAS, ECHO_PIN_ATAS);
  Serial.print("Jarak Atas: ");
  Serial.println(distance_atas);

  if (distance_bawah > 10) {
    stopMotors();
    delay(1000);
    moveBackward();
    delay(2000);
    stopMotors();
    return;
  }

  // Logika Ultrasonic Atas
  if (distance_atas < 15) { 
    stopMotors();
    myServo.write(45);
    delay(500);
    int leftDistance = getDistance(TRIG_PIN_ATAS, ECHO_PIN_ATAS);

    myServo.write(135);
    delay(500);
    int rightDistance = getDistance(TRIG_PIN_ATAS, ECHO_PIN_ATAS);

    myServo.write(90);

    if (leftDistance > rightDistance) {
      turnLeft();
      delay(250);
    } else {
      turnRight();
      delay(250);
    }

    stopMotors();
  } else {
    moveForward();
  }

  delay(100);
}
