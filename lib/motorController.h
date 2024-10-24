#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include <Arduino.h>

class motorController
{
private:
    char enableAddress;
    char poleAddress1;
    char poleAddress2;

    int velocity;
    bool polaritySense1;
    bool polaritySense2;
public:
    motorController(char pole1, char pole2, char enable);
    ~motorController();
    
    void changePolaritySense(bool sense);
    void changeVelocity(int velocity);
    void turnOff();
    void run();
};

#endif