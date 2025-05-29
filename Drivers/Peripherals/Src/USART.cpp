//
// Created by Admin on 5/26/2025.
//
#include "USART.h"

namespace Drivers::Peripherals
{
  extern USART usart6, uart7, uart8;
  USART::USART(
    UsartConfig cfg
    ):
    usartConfig(std::move(cfg))
  {
  }

  void USART::init()
  {
    UART_HandleTypeDef UART_Handle;
    UART_Handle.Init.BaudRate = this->usartConfig.BaudRate;
    UART_Handle.Init.WordLength = this->usartConfig.WordLength;
    UART_Handle.Init.StopBits = this->usartConfig.StopBits;
    UART_Handle.Init.Parity = this->usartConfig.Parity;
    UART_Handle.Init.Mode = this->usartConfig.USART_Mode;
    UART_Handle.Init.HwFlowCtl = this->usartConfig.HwFlowCtl;
    UART_Handle.Init.OverSampling = this->usartConfig.OverSampling;
    UART_Handle.Instance = this->usartConfig.USARTx;
    HAL_UART_Init(&UART_Handle);

    if (this->usartConfig.interruptFlag != 0)
    {
      __HAL_USART_ENABLE_IT(&UART_Handle, this->usartConfig.interruptFlag);
    }
  }

  void USART::globalInitCallback_Default()
  {
    usart6.init();
    uart7.init();
    uart8.init();
  }

  void USART::globalInit()
  {
    globalInitCallback();
  }

}
