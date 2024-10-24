#ifndef MEASURATE_IMU_H
#define MEASURATE_IMU_H

class measurateIMU
{
private:
    float xVeloc, yVeloc, zVeloc;
    float xPos  , yPos  , zPos;
    float roll  , pitch , yaw;
    float alpha;

public:
    measurateIMU(float alpha);
    ~measurateIMU();

    void updateAngle(float accIMU[3], float gyroIMU[3], float deltaTime);
    void updateVelocity(float accIMU[3], float deltaTime);
    void returnAngle(float *gyroX, float *gyroY, float *gyroZ);
    void returnVelocity(float *vlcX, float *vlcY, float *avlcZ);
    void returnPosition(float *posX, float *posY, float *posZ);

    float LowPassFilter(float value);
};

#endif