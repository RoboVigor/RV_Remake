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
  public:
    struct SPIConfig
    {
      SPI_TypeDef* SPIx;
      uint32_t Mode = SPI_MODE_MASTER;
      uint32_t Direction = SPI_DIRECTION_2LINES;
      uint32_t DataSize = SPI_DATASIZE_8BIT;
      uint32_t CLKPolarity = SPI_POLARITY_LOW;
      uint32_t CLKPhase = SPI_PHASE_1EDGE;
      uint32_t NSS = SPI_NSS_HARD_OUTPUT;
      uint32_t BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
      uint32_t FirstBit = SPI_FIRSTBIT_MSB;
      uint32_t TIMode = SPI_TIMODE_DISABLE;
      uint32_t CRCCalculation = SPI_CRCCALCULATION_DISABLE;
      uint32_t CRCPolynomial = NULL;
      uint32_t interruptFlag;
    };
  private:
    SPIConfig spiConfig;

    static void globalInitCallback_Default();

  public:
    SPI();
    explicit SPI(
      SPIConfig spiConfig
      );
    static void globalInit();
    static inline void (*globalInitCallback)() = globalInitCallback_Default;
    void transmit(uint8_t *data, uint16_t length);
    void recieve(uint8_t *buffer, uint16_t length);
    void transmit_recive(uint8_t *data, uint8_t *buffer, uint16_t TXlength, uint16_t RXlength, uint8_t RXDMAEnabled);
    void init();
  };
}

#endif //SPI_H
