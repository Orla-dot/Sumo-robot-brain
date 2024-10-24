#include "motorController.h"

motorController::motorController(char pole1, char pole2, char enable) {
    poleAddress1 = pole1;
    poleAddress2 = pole2;
    enableAddress = enable;

    pinMode(poleAddress1, OUTPUT);
    pinMode(poleAddress2, OUTPUT);
    pinMode(enableAddress, OUTPUT);
}
motorController::~motorController();
    
void motorController::changePolaritySense(bool sense) {
    polaritySense1 =  sense;
    polaritySense1 = !sense;
}
void motorController::changeVelocity(int velocity) {
    velocity = velocity;
}
void motorController::turnOff() {
    polaritySense1 = LOW;
    polaritySense2 = LOW;
}
void motorController::run() {
    digitalWrite(poleAddress1, polaritySense1);
    digitalWrite(poleAddress2, polaritySense2);
    analogWrite(enableAddress, velocity);
}