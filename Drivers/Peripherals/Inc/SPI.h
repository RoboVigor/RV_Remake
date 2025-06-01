/**
* Author: Rian
* Date: 6/1/2025.
*/

#ifndef SPI_H
#define SPI_H

#include "stm32f4xx_hal.h"

namespace Drivers::Peripherals
{
  class SPI
  {
  private:
    struct SPIConfig
    {
      SPI_TypeDef* SPIx;
      uint32_t Mode;
      uint32_t Direction;
      uint32_t DataSize;
      uint32_t CLKPolarity;
      uint32_t CLKPhase;
      uint32_t NSS;
      uint32_t BaudRatePrescaler;
      uint32_t FirstBit;
      uint32_t TIMode;
      uint32_t CRCCalculation;
      uint32_t CRCPolynomial;
      uint32_t interruptFlag;
    };

    SPIConfig spiConfig;
    void init();
    static void globalInitCallback_Default();
    void transmit(uint8_t *data, uint16_t length);
    void recieve(uint8_t *buffer, uint16_t length);
    void transmit_recive(uint8_t *data, uint8_t *buffer, uint16_t TXlength, uint16_t RXlength, uint8_t RXDMAEnabled);
  public:
    SPI(
      SPIConfig spiConfig
      );
    static void globalInit();
    static inline void (*globalInitCallback)() = globalInitCallback_Default;
  };
}

#endif //SPI_H
