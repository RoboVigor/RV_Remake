/**
* Author: Rian
* Date: 6/16/2025.
*/

#ifndef MOTOR_H
#define MOTOR_H
#include <list>
#include <map>


#include "PROTOCOL.h"

namespace Drivers::APP
{
  class MOTOR
  {
  public:
    struct MotorInfo
    {
      /* basic info */
      PROTOCOL* protocol;
      uint16_t motorID;

      /* config */
      float reduction;
      uint8_t continuousAngleEnbale;
      uint16_t currentResolution;
      float angleBias = 0;

      /* data */
      float speed;
      float angle;
      float current;
      int16_t temperature;
      float actualAngle;
      float lastActualAngle;
      int16_t round = 0;
    };

    MotorInfo motorInfo;

    typedef std::pmr::map<uint16_t, uint16_t> MotorDataMap;
    static inline MotorDataMap motorDataMap = motorBindMap;

    MOTOR();
    explicit MOTOR(MotorInfo motorInfo);

    void setBias(float bias);
    void bind(uint16_t ID, CAN_TypeDef* CANx);
    static void motorUpdate(std::pmr::list<MOTOR> motorList);
  };
}
#endif //MOTOR_H
