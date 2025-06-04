/**
* Author: Rian
* Date: 6/4/2025.
*/

#ifndef MPU6500_H
#define MPU6500_H

#include "stm32f4xx_hal.h"
#include "REG_MPU6500_IST8310.h"
#include "SPI.h"

namespace Drivers::BSP
{
  class MPU6500
  {
  private:
    Peripherals::SPI SPIx;
  public:
  struct Config
  {
    uint8_t DLPF;
    uint8_t SampleDiv;
  };

    Config config;
    explicit MPU6500(Config config);
    void init();
    void readData(uint8_t Addr, uint8_t* buffer, uint16_t length);
  };
}

#endif //MPU6500_H
