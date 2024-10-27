#include "motorController.h"

// 
motorController::motorController(char pole1, char pole2, char enable) {
    setPole1(pole1);
    setPole2(pole2);
    setEnable(enable);
}
motorController::~motorController() {}

// public controller
void motorController::changeVelocitySensed(int veloc) {
    changePolaritySense(veloc > 0);
    changeVelocity(veloc);
}
void motorController::changePolaritySense(bool sense) {
    polaritySense1 =  sense;
    polaritySense1 = !sense;
}
void motorController::changeVelocity(int veloc) {
    velocity = min(abs(veloc), 255);
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

// privated variables
void motorController::setPole1(char pole1) {
    poleAddress1 = pole1;
    pinMode(poleAddress1, OUTPUT);
}
void motorController::setPole2(char pole2) {
    poleAddress2 = pole2;
    pinMode(poleAddress2, OUTPUT);
}
void motorController::setEnable(char enable) {
    enableAddress = enable;
    pinMode(enableAddress, OUTPUT);
}