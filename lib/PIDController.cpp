#include "PIDController.h"

PID::PID(double Kp, double Ki, double Kd) {
    insertConstants(Kp, Ki, Kd);
}
PID::~PID() {}

void PID::insertConstants(double Kp, double Ki, double Kd) {
    insertContantP(Kp);
    insertContantI(Ki);
    insertContantD(Kd);
}

inline void PID::insertContantP(double Kp) {K_p = Kp;}
inline void PID::insertContantI(double Ki) {K_i = Ki;}
inline void PID::insertContantD(double Kd) {K_d = Kd;}

double PID::returnP() {return p_output;}
double PID::returnI() {return i_output;}
double PID::returnD() {return d_output;}

void PID::rangeOfIntegral(int max, int min) {
    if (max <= min) return;

    integralMax = max;
    integralMin = min;
}
void PID::rangeOfOutput(int max, int min) {
    if (max <= min) return;

    outputMax = max;
    outputMin = min;
}

void PID::setSampleTime(uint32_t newTime) {
    if (newTime == 0) return;

    if (sampleTime == 0) {
        sampleTime = newTime;
        return;
    }

    double ration = (double)newTime / (double)sampleTime;

    K_i *= ration;
    K_d /= ration;

    sampleTime = newTime;
}

int PID::controll(int error) {
    double currentTime = millis();

    if (currentTime - previousTime >= sampleTime) {
        // proportional calculation
        if (K_p != 0) {
            p_output = K_p * error;
        }
        // integral calculation
        if (K_i != 0) {
            i_output += K_i * error;
        }
        // derivat calculation
        if (K_d != 0) {
            d_output = K_d * ((error - previousError)/(sampleTime));
            previousTime = currentTime;
        }

        int pid_output = p_output + i_output + d_output;

        if (pid_output > outputMax) pid_output = outputMax;
        if (pid_output < outputMin) pid_output = outputMin;

        return pid_output;
    }
}