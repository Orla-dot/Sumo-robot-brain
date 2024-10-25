#ifndef PID_Controller_H
#define PID_Controller_H

#include <SPI.h>
#include <Arduino.h>

class PID {
private:
    // pid outputs
    double p_output = 0;
    double i_output = 0;
    double d_output = 0;
    // pid constants
    double K_p = 0;
    double K_i = 0;
    double K_d = 0;

    // ranges of
    double integralMax = 0, integralMin = 0; // min and max integral value
    double outputMax = 0, outputMin = 0;     // min and max output value

    // previous values of
    uint64_t previousTime = 0;  // time
    uint32_t sampleTime   = 0;
    int previousError = 0; // errors

public:
    PID(double K_p, double K_i, double K_d);
    ~PID();

    void insertConstants(double K_p, double K_i, double K_d);
    void insertContantP(double K_p);
    void insertContantI(double K_i);
    void insertContantD(double K_d);
    double returnP();
    double returnI();
    double returnD();
    void rangeOfIntegral(double min, double max);
    void rangeOfOutput(double min, double max);
    void setSampleTime(uint32_t newTime);

    double controll(double error);
    double controll(double error, uint32_t sampleTime);
};

#endif