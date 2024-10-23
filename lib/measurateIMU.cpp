#include "measurateIMU.h"
#include "Arduino.h"

measurateIMU::measurateIMU(float alpha){
    alpha = alpha;
}

void measurateIMU::updateAngle(float accIMU[3], float gyroIMU[3], float deltaTime) {
    float rollAcc = atan2(accIMU[0], accIMU[2]) * (180.0f / PI);
    float pitchAcc = atan2(-accIMU[0] , sqrt(accIMU[1]*accIMU[1] + accIMU[2]*accIMU[2])) * (180.0f / PI);

    roll  += alpha * (roll + gyroIMU[0] * deltaTime) + (1.0f - alpha) * rollAcc;
    pitch += alpha * (pitch + gyroIMU[1] * deltaTime) + (1.0f - alpha) * pitchAcc;
    yaw   += gyroIMU[2] * deltaTime;
}
void measurateIMU::updateVelocity(float accIMU[3], float deltaTime) {
    xVeloc += accIMU[0] * deltaTime;
    yVeloc += accIMU[1] * deltaTime;
    zVeloc += accIMU[2] * deltaTime;

    xVeloc = LowPassFilter(xVeloc);
    yVeloc = LowPassFilter(yVeloc);
    zVeloc = LowPassFilter(zVeloc);
}
void measurateIMU::returnAngle(float *gyroX, float *gyroY, float *gyroZ) {
    *gyroX = roll;
    *gyroY = pitch;
    *gyroZ = yaw;
}
void measurateIMU::returnVelocity(float *accX, float *accY, float *accZ) {
    *accX = xVeloc;
    *accY = yVeloc;
    *accZ = zVeloc;
}

float measurateIMU::LowPassFilter(float value) {
    static float lastValue = 0.0f;

    lastValue = alpha * lastValue + (1 - alpha) * value;
    return lastValue;
}