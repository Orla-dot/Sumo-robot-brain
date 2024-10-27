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

    void setPole1(char pole1);
    void setPole2(char pole1);
    void setEnable(char enable);

public:
    motorController(char pole1, char pole2, char enable);
    ~motorController();
    
    void changeVelocitySensed(int veloc);
    void changePolaritySense(bool sense);
    void changeVelocity(int veloc);
    void turnOff();
    void run();
};

#endif