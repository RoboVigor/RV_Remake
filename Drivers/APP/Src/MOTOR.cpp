/**
 * Author: Rian
 * Date: 6/16/2025.
 */
#include "MOTOR.h"


namespace Drivers::APP
{
  MOTOR::MOTOR(MotorInfo motorInfo) : motorInfo(std::move(motorInfo)) {}

  void MOTOR::setBias(float bias) { this->motorInfo.angleBias = bias; }

  void MOTOR::bind(uint16_t ID, CAN_TypeDef* CANx)
  {
    this->motorInfo.motorID = ID | (CANx == CAN1 ? 0x1000 : 0x2000);
    if (this->motorInfo.protocol->protocolMap[this->motorInfo.motorID].protocolType == Dji_Motor)
    {
      uint32_t addr =
        reinterpret_cast<uint32_t>(this->motorInfo.protocol->protocolMap[motorDataMap[this->motorInfo.motorID]].TXdata +
                                   2 * ((this->motorInfo.motorID | 0xff) % 4 - 1));
      for (int i = 0; i < 4; ++i)
      {
        *(this->motorInfo.protocol->protocolMap[this->motorInfo.motorID].TXdata + i) = (addr >> 8 * i) & 0xff;
      }
    }
  }

  void MOTOR::motorUpdate(std::pmr::list<MOTOR> motorList)
  { /* 按电机协议类型特化 */
    for (MOTOR motor : motorList)
    {
      switch (motor.motorInfo.protocol->protocolMap[motor.motorInfo.motorID].protocolType)
      {
      default:
        break;

      case ProtocolType::Dji_Motor:
        uint8_t* data = motor.motorInfo.protocol->protocolMap[motor.motorInfo.motorID].RXdata;
        /* angle */
        motor.motorInfo.lastActualAngle = motor.motorInfo.actualAngle;
        motor.motorInfo.actualAngle = ((*data << 8) + *(data + 1)) / 8191.0f * 2* std::numbers::pi;
        float diff = motor.motorInfo.actualAngle - motor.motorInfo.lastActualAngle;
        if (diff < -std::numbers::pi/2.0f)
        {
          motor.motorInfo.round ++;
        }else if (diff > std::numbers::pi/2.0f)
        {
          motor.motorInfo.round --;
        }
        if (motor.motorInfo.continuousAngleEnbale)
        {

          motor.motorInfo.angle = (motor.motorInfo.actualAngle + motor.motorInfo.round * 2*std::numbers::pi)/motor.motorInfo.reduction - motor.motorInfo.angleBias;
        }
        else
        {
          float tempAngle = ((motor.motorInfo.actualAngle + motor.motorInfo.round * 2*std::numbers::pi)/motor.motorInfo.reduction) - motor.motorInfo.angleBias;
          if (tempAngle > 0)
          {
            /* 这个写法比较邪门，很可能被骂不建议大家学 */
            for (tempAngle; tempAngle > 2*std::numbers::pi; tempAngle -= 2*std::numbers::pi);
          }else if (tempAngle < 0)
          {
            for (tempAngle; tempAngle < 0; tempAngle += 2*std::numbers::pi);
          }
          motor.motorInfo.angle =  tempAngle;
        }
        /* speed */
        motor.motorInfo.speed = (*(data +2) << 8 | *(data + 3))*std::numbers::pi/30.0f/motor.motorInfo.reduction;
        /* current */
        motor.motorInfo.current = (*(data +4) << 8 | *(data + 5)) / (float)motor.motorInfo.currentResolution;
        /* temperature */
        motor.motorInfo.temperature = *(data + 6);
        break;
      }
    }
  }


} // namespace Drivers::APP
