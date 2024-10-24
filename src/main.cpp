#include <Arduino.h>
#include <iostream>

float fromLeftWheel = 0;
float fromRightWheel = 0;
float backLeftWheel = 0;
float backRightWheel = 0;



void setup() {
}

void loop() {
}




void internalDynamics(float xController, float yController, float yawController) {
    // calculating the velocity of all the wheels
    char velocityMotor1 = xController + yController + yawController;
    char velocityMotor2 = xController - yController + yawController;
    char velocityMotor3 = xController + yController - yawController;
    char velocityMotor4 = xController - yController - yawController;
    
    // seting the polarity/sense of the motors
    bool polarityMotor1 = (velocityMotor1 < 0);
    bool polarityMotor2 = (velocityMotor2 < 0);
    bool polarityMotor3 = (velocityMotor3 < 0);
    bool polarityMotor4 = (velocityMotor4 < 0);

    // turnung absolut and limiting a value
    velocityMotor1 = max(abs(velocityMotor1), 255);
    velocityMotor2 = max(abs(velocityMotor2), 255);
    velocityMotor3 = max(abs(velocityMotor3), 255);
    velocityMotor4 = max(abs(velocityMotor4), 255);
}