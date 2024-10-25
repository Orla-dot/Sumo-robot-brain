#include <Arduino.h>
#include "..\lib\measurateIMU.h"
#include "..\lib\PIDController.h"
#include "..\lib\motorController.h"

// motors controllers
motorController motor1(22, 23, 2);
motorController motor2(24, 25, 3);
motorController motor3(26, 27, 4);
motorController motor4(28, 29, 5);
// controllers of the robot
PID controllerX(10, 0, 0.2);
PID controllerY(10, 0, 0.2);
PID controllerYAW(10, 0, 0.2);



void setup() {
    controllerX.rangeOfOutput(-255, 255);
    controllerY.rangeOfOutput(-255, 255);
    controllerYAW.rangeOfOutput(-255, 255);


}

void loop() {
}


void pathPlanning(bool signal, bool arena1, bool arena2, bool arena3, bool arena4) {

}

void internalDynamics(double xController, double yController, double yawController) {
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

    // changing variables
    // - changing polarity & velocity
    motor1.changeSenseEVelocity(polarityMotor1, velocityMotor1);
    motor2.changeSenseEVelocity(polarityMotor2, velocityMotor2);
    motor3.changeSenseEVelocity(polarityMotor3, velocityMotor3);
    motor4.changeSenseEVelocity(polarityMotor4, velocityMotor4);

    // run
    motor1.run();
    motor2.run();
    motor3.run();
    motor4.run();
}