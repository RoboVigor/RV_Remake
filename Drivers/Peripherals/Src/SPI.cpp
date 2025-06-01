/**
* Author: Rian
* Date: 6/1/2025.
*/
#include "SPI.h"

#include <algorithm>

#include "stm32f4xx_ll_spi.h"

namespace Drivers::Peripherals
{
  extern SPI spi5;
  SPI::SPI(SPIConfig spiConfig) :
    spiConfig(std::move(spiConfig))
  {
  }

  void SPI::init()
  {
    SPI_HandleTypeDef spiHandle;
    spiHandle.Instance = this->spiConfig.SPIx;
    spiHandle.Init.Mode = this->spiConfig.Mode;
    spiHandle.Init.Direction = this->spiConfig.Direction;
    spiHandle.Init.CLKPolarity = this->spiConfig.CLKPolarity;
    spiHandle.Init.CLKPhase = this->spiConfig.CLKPhase;
    spiHandle.Init.DataSize = this->spiConfig.DataSize;
    spiHandle.Init.FirstBit = this->spiConfig.FirstBit;
    spiHandle.Init.NSS = this->spiConfig.NSS;
    spiHandle.Init.BaudRatePrescaler = this->spiConfig.BaudRatePrescaler;
    spiHandle.Init.TIMode = this->spiConfig.TIMode;
    spiHandle.Init.CRCCalculation = this->spiConfig.CRCCalculation;
    spiHandle.Init.CRCPolynomial = this->spiConfig.CRCPolynomial;
    HAL_SPI_Init(&spiHandle);

    if (this->spiConfig.interruptFlag != 0)
    {
      __HAL_SPI_ENABLE_IT(&spiHandle, this->spiConfig.interruptFlag);
    }
  }

  void SPI::globalInitCallback_Default()
  {
    spi5.init();
  }

  void SPI::globalInit()
  {
    globalInitCallback();
  }

  void SPI::transmit(uint8_t* data, uint16_t length)
  {
    for (int i = 0; i < length; i++)
    {
      while (!LL_SPI_IsActiveFlag_TXE(this->spiConfig.SPIx)){};
      LL_SPI_TransmitData8(this->spiConfig.SPIx, *(data + i));

      while (!LL_SPI_IsActiveFlag_RXNE(this->spiConfig.SPIx)){};
      LL_SPI_ReceiveData8(this->spiConfig.SPIx);
    }
    while (!LL_SPI_IsActiveFlag_TXE(this->spiConfig.SPIx) && LL_SPI_IsActiveFlag_BSY(this->spiConfig.SPIx)){};
  }

  void SPI::recieve(uint8_t* buffer, uint16_t length)
  {
    for (int i = 0; i < length; i++)
    {
      while (!LL_SPI_IsActiveFlag_TXE(this->spiConfig.SPIx)){};
      LL_SPI_TransmitData8(this->spiConfig.SPIx, 0xff);

      while (!LL_SPI_IsActiveFlag_RXNE(this->spiConfig.SPIx)){};
      *(buffer + i) = LL_SPI_ReceiveData8(this->spiConfig.SPIx);
    }
    while (!LL_SPI_IsActiveFlag_TXE(this->spiConfig.SPIx) && LL_SPI_IsActiveFlag_BSY(this->spiConfig.SPIx)){};
  }

  void SPI::transmit_recive(uint8_t* data, uint8_t* buffer, uint16_t TXlength, uint16_t RXlength, uint8_t RXDMAEnabled)
  {
    uint32_t totalLength = TXlength + RXlength;
    for (uint32_t i = 0; i < totalLength; i++)
    {
      while (!LL_SPI_IsActiveFlag_TXE(this->spiConfig.SPIx)){};
      if (i < TXlength)
      {
        LL_SPI_TransmitData8(this->spiConfig.SPIx, *(data + i));
      }
      else
      {
        LL_SPI_TransmitData8(this->spiConfig.SPIx, 0xff);
      }

      if (!RXDMAEnabled)
      {
        if (i < TXlength)
        {
          LL_SPI_ReceiveData8(this->spiConfig.SPIx);
        }
        else
        {
          *(buffer + i) = LL_SPI_ReceiveData8(this->spiConfig.SPIx);
        }
      }
    }
    while (!LL_SPI_IsActiveFlag_TXE(this->spiConfig.SPIx) && LL_SPI_IsActiveFlag_BSY(this->spiConfig.SPIx)){};
  }


}
