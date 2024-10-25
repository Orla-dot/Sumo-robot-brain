#include "measurateIMU.h"
#include "Arduino.h"

// public methods
measurateIMU::measurateIMU(float alpha){
    alpha = alpha;
}
// --- updating values
void measurateIMU::updateAngle(float accIMU[3], float gyroIMU[3], float deltaTime) {
    // calculating the angles of the acceleration
    float rollAcc = atan2(accIMU[0], accIMU[2]) * (180.0f / PI);
    float pitchAcc = atan2(-accIMU[0] , sqrt(accIMU[1]*accIMU[1] + accIMU[2]*accIMU[2])) * (180.0f / PI);

    // Math of the angles
    roll  += alpha * (roll + gyroIMU[0] * deltaTime) + (1.0f - alpha) * rollAcc;
    pitch += alpha * (pitch + gyroIMU[1] * deltaTime) + (1.0f - alpha) * pitchAcc;
    yaw   += gyroIMU[2] * deltaTime;
}
void measurateIMU::updateVelocity(float accIMU[3], float deltaTime) {
    // adding the IMU inert valet and multiply by the diferential time
    xVeloc += accIMU[0] * deltaTime;
    yVeloc += accIMU[1] * deltaTime;
    zVeloc += accIMU[2] * deltaTime;

    // passing the low pass filter to the velocity
    xVeloc = LowPassFilter(xVeloc);
    yVeloc = LowPassFilter(yVeloc);
    zVeloc = LowPassFilter(zVeloc);
}
void measurateIMU::updatePosition(float accIMU[3], float deltaTime) {
    // adding the IMU inert valet and multiply by the diferential time
    xVeloc += accIMU[0] * deltaTime;
    yVeloc += accIMU[1] * deltaTime;
    zVeloc += accIMU[2] * deltaTime;

    // passing the low-pass filter to the position
    xPos   = LowPassFilter(xVeloc * deltaTime);
    yPos   = LowPassFilter(yVeloc * deltaTime);
    zPos   = LowPassFilter(zVeloc * deltaTime);
}
// --- return variables
void measurateIMU::returnAngle(float *gyroX, float *gyroY, float *gyroZ) {
    *gyroX = roll;
    *gyroY = pitch;
    *gyroZ = yaw;
}
void measurateIMU::returnVelocity(float *vlcX, float *vlcY, float *vlcZ) {
    *vlcX = xVeloc;
    *vlcY = yVeloc;
    *vlcZ = zVeloc;
}
void measurateIMU::returnPosition(float *posX, float *posY, float *posZ) {
    *posX = xPos;
    *posY = yPos;
    *posZ = zPos;
}

// private methods
float measurateIMU::LowPassFilter(float value) {
    static float lastValue = 0.0f;

    lastValue = alpha * lastValue + (1 - alpha) * value;
    return lastValue;
}
