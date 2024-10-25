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

void PID::rangeOfIntegral(double min, double max) {
    if (max <= min) return;

    integralMax = max;
    integralMin = min;
}
void PID::rangeOfOutput(double min, double max) {
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

double PID::controll(double error) {
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
            previousError = error;
        }

        double pid_output = p_output + i_output + d_output;
        pid_output = (max(pid_output, outputMax), outputMin);

        return pid_output;
    }
}
double PID::controll(double error, uint32_t sampleTime) {
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
        previousError = error;
    }

    double pid_output = p_output + i_output + d_output;
    pid_output = (max(pid_output, outputMax), outputMin);

    return pid_output;
}
