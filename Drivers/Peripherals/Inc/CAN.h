//
// Created by Admin on 5/26/2025.
//
#ifndef CAN_H
#define CAN_H
#include "stm32f4xx_hal.h"

namespace Drivers::Peripherals
{
  class CAN
  {
    public:
    struct CANConfig
    {
      CAN_TypeDef* CANx;
      uint32_t Prescaler = 3;
      uint32_t Mode = CAN_MODE_NORMAL;
      uint32_t SyncJumpWidth = CAN_SJW_1TQ;
      uint32_t TimeSeg1 = CAN_BS1_9TQ;
      uint32_t TimeSeg2 = CAN_BS2_5TQ;
      FunctionalState TimeTriggeredMode = DISABLE;
      FunctionalState AutoBusOff = DISABLE;
      FunctionalState AutoWakeUp = DISABLE;
      FunctionalState AutoRetransmission = DISABLE;
      FunctionalState ReceiveFifoLocked = DISABLE;
      FunctionalState TransmitFifoPriority = DISABLE;
      uint32_t interruptFlag;
    };

    struct FilterConfig
    {
      uint32_t FilterIdHigh;
      uint32_t FilterIdLow;
      uint32_t FilterMaskIdHigh;
      uint32_t FilterMaskIdLow;
      uint32_t FilterFIFOAssignment;
      uint32_t FilterBank;
      uint32_t FilterMode;
      uint32_t FilterScale;
      uint32_t FilterActivation;
      uint32_t SlaveStartFilterBank;
    };
  private:
    CANConfig canConfig;
    FilterConfig filterConfig;

    static void globalInitCallback_Default();

    public:
    explicit CAN(
      CANConfig canConfig, FilterConfig filterConfig
      );
    static void globalInit();
    static inline void (* globalInitCallback) () = globalInitCallback_Default;
    void canSend(uint16_t stdID, uint8_t data[8]);
    void canSendMessage(uint16_t stdID, uint8_t *sendBuffer, uint16_t length);
    static void canTransmit(CAN_TypeDef* CANx, CAN_TxHeaderTypeDef* canTxData, uint8_t data[8]);
    void init();

  };
}
#endif //CAN_H
