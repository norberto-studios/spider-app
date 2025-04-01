#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
// #include <ESP32Servo.h>
#include "logger.h"

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define POT_PIN A0  // Analog input from potentiometer
#define SERVO_PIN D1  // PWM output for the servo

#define SERVO_MIN 80 // this is the 'minimum' pulse length count (out of 4096)
#define SERVO_MAX 500 // this is the 'maximum' pulse length count (out of 4096)
#define SERVO_CENTER ((SERVO_MIN + SERVO_MAX) / 2)
#define SERVO_FREQUENCY 50 // 50Hz for servos

#define SERVO_COXA  0
#define SERVO_FEMUR 1
#define SERVO_TIBIA 2

// Servo myServo;  // Create a Servo object

// void moveServo(int potValue) {
//     // Map potentiometer value to servo range (0° to 180°)
//     int servoAngle = map(potValue, 0, 4095, 0, 180);
//
//     // Debug output
//     Serial.printf("Potentiometer: %d \n", potValue);
//     Serial.print(" | Servo Pulse: "); Serial.println(servoAngle);
//
//
//     // Move the servo
//     myServo.write(servoAngle);
//     delay(20); // Small delay to avoid excessive updates
//
// }
void moveServo(int servo, int angle) {
    int pulse = map(angle, 0, 180, SERVO_MIN, SERVO_MAX);
    pwm.setPWM(servo, 0, pulse);
}
int readServoPosition() {
    int sensorValue = analogRead(POT_PIN);
    return map(sensorValue, 0, 4095, 0, 180);  // Convert to degrees
}

void setup() {
    Serial.begin(115200);
    // Initialize the PWM driver
    pwm.begin();
    pwm.setPWMFreq(SERVO_FREQUENCY);

    // reset servos

    delay(10);
}

void loop() {

    // // logMessage("PotValue: "+potValue);
    //
    // // heartbeat(); // Logger Heartbeat

    if (Serial.available()) {
        String command = Serial.readStringUntil('\n');
        int coxaAngle = command.substring(0, command.indexOf(',')).toInt();
        command = command.substring(command.indexOf(',') + 1);
        int femurAngle = command.substring(0, command.indexOf(',')).toInt();
        int tibiaAngle = command.substring(command.indexOf(',') + 1).toInt();

        moveServo(SERVO_COXA, coxaAngle);
        moveServo(SERVO_FEMUR, femurAngle);
        moveServo(SERVO_TIBIA, tibiaAngle);

        delay(300);  // Allow time for movement

        Serial.printf("ACK: Coxa %d°, Femur %d°, Tibia %d° | Feedback: %d°\n", coxaAngle, femurAngle, tibiaAngle);
    }
}
