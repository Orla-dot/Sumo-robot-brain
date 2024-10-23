#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

class motorController
{
private:
    int enable;
    char pole1;
    char pole2;
    bool poleSense1;
    bool poleSense2;
public:
    motorController(char pole1, char pole2);
    ~motorController();
    
    void changePoleSense(bool sense);
    void changeVelocity(int velocity);
    void run();
};

#endif