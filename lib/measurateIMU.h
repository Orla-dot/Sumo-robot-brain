#ifndef MEASURATE_IMU_H
#define MEASURATE_IMU_H

class measurateIMU
{
private:
    float xVeloc, yVeloc, zVeloc;
    float roll  , pitch , yaw;
    float alpha;

public:
    measurateIMU(float alpha);
    ~measurateIMU();

    void updateAngle(float accIMU[3], float gyroIMU[3], float deltaTime);
    void updateVelocity(float accIMU[3], float deltaTime);
    void returnAngle(float *gyroX, float *gyroY, float *gyroZ);
    void returnVelocity(float *accX, float *accY, float *accZ);

    float LowPassFilter(float value);
};

#endif