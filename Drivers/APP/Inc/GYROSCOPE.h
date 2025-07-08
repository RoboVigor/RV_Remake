/**
* Author: Rian
* Date: 6/24/2025.
*/

#ifndef GYROSCOPE_H
#define GYROSCOPE_H
#include "MPU6500.h"

namespace Drivers::APP
{
  class GYROSCOPE
  {
  public:
    struct GyroscopeInfo
    {
      BSP::MPU6500 mpu6500;
      float xSpeed;
      float ySpeed;
      float zSpeed;
      float rollSpeed;
      float pitchSpeed;
      float yawSpeed;
      float rollAngle;
      float pitchAngle;
      float yawAngle;
    };

    GyroscopeInfo gyroscopeInfo;

    GYROSCOPE();
    explicit GYROSCOPE(GyroscopeInfo gyroscopeInfo);

    void gyroscopeUpdate();
    static void (*gyroscopeUpdateCallback) (GYROSCOPE* gyroscope);
  };
}

#endif //GYROSCOPE_H
