//
// Created by Admin on 5/26/2025.
//

#ifndef USART_H
#define USART_H
#include  "stm32f4xx_hal.h"
#include "utility"

namespace Drivers::Peripherals
{

  class USART
  {
  private: struct UsartConfig
    {
      USART_TypeDef* USARTx;
      uint32_t BaudRate;
      uint32_t WordLength = UART_WORDLENGTH_8B;
      uint32_t StopBits = UART_STOPBITS_1;
      uint32_t Parity = UART_PARITY_NONE;
      uint32_t USART_Mode = UART_MODE_TX_RX;
      uint32_t HwFlowCtl = UART_HWCONTROL_NONE;
      uint32_t OverSampling = UART_OVERSAMPLING_16;
      uint32_t interruptFlag;
    };

  private:
    UsartConfig usartConfig;
    static void globalInitCallback_Default(void);

  public:
    /*
     * class structure func
     */
    explicit USART(UsartConfig cfg);
    /*
     * func
     */
    static void globalInit(void);
    static inline void (*globalInitCallback)(void) = globalInitCallback_Default;
    void init();

  };
}
#endif //USART_H
