/**
* Author: Rian
* Date: 5/29/2025.
*/
#include "CAN.h"

#include <algorithm>

namespace Drivers::Peripherals
{
  extern CAN can1, can2;

  CAN::CAN(CANConfig canConfig, FilterConfig filterConfig) :
    canConfig(std::move(canConfig)), filterConfig(std::move(filterConfig))
  {
  }

  void CAN::init()
  {
    CAN_HandleTypeDef canHandle;
    canHandle.Instance = this->canConfig.CANx;
    canHandle.Init.Prescaler = this->canConfig.Prescaler;
    canHandle.Init.Mode = this->canConfig.Mode;
    canHandle.Init.SyncJumpWidth = this->canConfig.SyncJumpWidth;
    canHandle.Init.TimeSeg1 = this->canConfig.TimeSeg1;
    canHandle.Init.TimeSeg2 = this->canConfig.TimeSeg2;
    canHandle.Init.TimeTriggeredMode = this->canConfig.TimeTriggeredMode;
    canHandle.Init.AutoBusOff = this->canConfig.AutoBusOff;
    canHandle.Init.AutoWakeUp = this->canConfig.AutoWakeUp;
    canHandle.Init.AutoRetransmission = this->canConfig.AutoRetransmission;
    canHandle.Init.ReceiveFifoLocked = this->canConfig.ReceiveFifoLocked;
    canHandle.Init.TransmitFifoPriority = this->canConfig.TransmitFifoPriority;
    HAL_CAN_Init(&canHandle);

    CAN_FilterTypeDef filterHandle;
    filterHandle.FilterIdHigh = this->filterConfig.FilterIdHigh;
    filterHandle.FilterIdLow = this->filterConfig.FilterIdLow;
    filterHandle.FilterMaskIdHigh = this->filterConfig.FilterMaskIdHigh;
    filterHandle.FilterMaskIdLow = this->filterConfig.FilterMaskIdLow;
    filterHandle.FilterFIFOAssignment = this->filterConfig.FilterFIFOAssignment;
    filterHandle.FilterActivation = this->filterConfig.FilterActivation;
    filterHandle.FilterBank = this->filterConfig.FilterBank;
    filterHandle.FilterMode = this->filterConfig.FilterMode;
    filterHandle.FilterScale = this->filterConfig.FilterScale;
    filterHandle.SlaveStartFilterBank = this->filterConfig.SlaveStartFilterBank;
    HAL_CAN_ConfigFilter(&canHandle, &filterHandle);

    if (this->canConfig.interruptFlag != 0)
    {
      __HAL_CAN_ENABLE_IT(&canHandle, this->canConfig.interruptFlag);
    }

  }

  void CAN::globalInitCallback_Default()
  {
    can1.init();
    can2.init();
  }

  void CAN::globalInit()
  {
    globalInitCallback();
  }

  void CAN::canSend(uint16_t stdID, uint8_t data[8])
  {
    CAN_TxHeaderTypeDef canTxData;
    canTxData.IDE = CAN_ID_STD;
    canTxData.StdId = stdID;
    canTxData.RTR = CAN_RTR_DATA;
    canTxData.DLC = 8;
    canTxData.ExtId = NULL;

    canTransmit(this->canConfig.CANx, &canTxData, data);
  }

  void CAN::canSendMessage(uint16_t stdID, uint8_t* sendBuffer, uint16_t length)
  {
    uint8_t k = (length / 8) + (length % 8 != 0 ? 1 : 0);
    for (uint8_t i = 0; i < k; i++)
    {
      canSend(stdID, (sendBuffer + i * 8));
    }
  }


  void CAN::canTransmit(CAN_TypeDef* CANx, CAN_TxHeaderTypeDef* canTxData, uint8_t data[8])
  {
    uint8_t mailBox;
    if (
      (CANx->TSR & CAN_TSR_TME0) != 0 ||
      (CANx->TSR & CAN_TSR_TME1) != 0 ||
      (CANx->TSR & CAN_TSR_TME2) != 0)
    {
      mailBox = (CANx->TSR & CAN_TSR_CODE) >> CAN_TSR_CODE_Pos;
    }
    else
    {
      return;
    }

    if (canTxData->IDE == CAN_ID_STD)
    {
      CANx->sTxMailBox[mailBox].TIR = (canTxData->StdId << CAN_TI0R_IDE_Pos | canTxData->RTR);
    }
    else
    {
      CANx->sTxMailBox[mailBox].TIR = (canTxData->ExtId << CAN_TI0R_EXID_Pos | canTxData->IDE | canTxData->RTR);
    }

    CANx->sTxMailBox[mailBox].TDTR = canTxData->DLC;

    if (canTxData->TransmitGlobalTime)
    {
      CANx->sTxMailBox[mailBox].TDTR |= CAN_TDT0R_TGT;
    }

    CANx->sTxMailBox[mailBox].TDLR = (((uint32_t)data[0] << CAN_TDL0R_DATA0_Pos) |
      ((uint32_t)data[1] << CAN_TDL0R_DATA1_Pos) |
      ((uint32_t)data[2] << CAN_TDL0R_DATA2_Pos) |
      ((uint32_t)data[3] << CAN_TDL0R_DATA3_Pos));

    CANx->sTxMailBox[mailBox].TIR |= CAN_TI0R_TXRQ;

    /* check and wait the transmission finished */
    while ((CANx->TSR & ((0x01 << mailBox) << CAN_TSR_TME0)) & ((0x01 << mailBox) << CAN_TSR_TME0) == 0)
    {}
  }

}
