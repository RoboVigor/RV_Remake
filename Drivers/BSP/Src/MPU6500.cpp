/**
* Author: Rian
* Date: 6/4/2025.
*/

#include "MPU6500.h"

#include <algorithm>

namespace Drivers::BSP
{
  MPU6500::MPU6500(Config config)
    :config(std::move(config))
  {
  }

  void MPU6500::init()
  {
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_SYSCFG_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    HAL_NVIC_SetPriority(EXTI9_5_IRQn, 7, 0);
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

    Peripherals::SPI spi5(Peripherals::SPI::SPIConfig{.SPIx = SPI5, .interruptFlag = 0});
    Peripherals::SPI::globalInit();
    this->SPIx = spi5;

    uint8_t tempAddr;
    uint8_t tempBuffer;
    uint8_t tempData;

    tempAddr = MPU6500_WHO_AM_I | 0x80;
    spi5.transmit_recive(&tempAddr, &tempBuffer, 1, 1, 0);
    if (tempBuffer != MPU6500_ID)
    {
      return;
    }

    union WriteData
    {
      struct
      {
        uint8_t addr;
        uint8_t Txdata;
      };

      struct
      {
        uint8_t data[2];
      };
    } writeData = {};

    writeData.addr = MPU6500_PWR_MGMT_1;
    writeData.Txdata = 0x01;
    spi5.transmit(writeData.data, 2);

    writeData.addr = MPU6500_USER_CTRL;
    writeData.Txdata = 0x30;
    spi5.transmit(writeData.data, 2);

    writeData.addr = MPU6500_GYRO_CONFIG;
    writeData.Txdata = 0x18;
    spi5.transmit(writeData.data, 2);

    writeData.addr = MPU6500_ACCEL_CONFIG;
    writeData.Txdata = 0x10;
    spi5.transmit(writeData.data, 2);

    writeData.addr = MPU6500_ACCEL_CONFIG_2;
    writeData.Txdata = 0x01;
    spi5.transmit(writeData.data, 2);

    writeData.addr = MPU6500_CONFIG;
    writeData.Txdata = 0x00 | this->config.DLPF;
    spi5.transmit(writeData.data, 2);

    writeData.addr = MPU6500_SMPLRT_DIV;
    writeData.Txdata = this->config.SampleDiv;
    spi5.transmit(writeData.data, 2);

    writeData.addr = MPU6500_I2C_MST_CTRL;
    writeData.Txdata = 0x5D;
    spi5.transmit(writeData.data, 2);

    writeData.addr = MPU6500_I2C_MST_DELAY_CTRL;
    writeData.Txdata = 0x81;
    spi5.transmit(writeData.data, 2);

    /* config IST8310 */
    writeData.addr = MPU6500_I2C_SLV4_ADDR;
    writeData.Txdata = 0x00 | IST8310_ADDRESS;
    spi5.transmit(writeData.data, 2);

    writeData.addr = MPU6500_I2C_SLV4_REG;
    writeData.Txdata = IST8310_R_CONFB;
    spi5.transmit(writeData.data, 2);

    writeData.addr = MPU6500_I2C_SLV4_DO;
    writeData.Txdata = 0x01;
    spi5.transmit(writeData.data, 2);

    writeData.addr = MPU6500_I2C_SLV4_CTRL;
    writeData.Txdata = 0x80;
    spi5.transmit(writeData.data, 2);

    HAL_Delay(100);

    writeData.addr = MPU6500_I2C_SLV4_REG;
    writeData.Txdata = IST8310_R_CONFA;
    spi5.transmit(writeData.data, 2);

    writeData.addr = MPU6500_I2C_SLV4_DO;
    writeData.Txdata = 0x0E;
    spi5.transmit(writeData.data, 2);

    writeData.addr = MPU6500_I2C_SLV4_CTRL;
    writeData.Txdata = 0x80;
    spi5.transmit(writeData.data, 2);

    HAL_Delay(100);

    /*auto read IST8310*/
    writeData.addr = MPU6500_I2C_SLV0_ADDR;
    writeData.Txdata = 0x80 | IST8310_ADDRESS;
    spi5.transmit(writeData.data, 2);

    writeData.addr = MPU6500_I2C_SLV0_REG;
    writeData.Txdata = IST8310_R_XL;
    spi5.transmit(writeData.data, 2);

    writeData.addr = MPU6500_I2C_SLV0_CTRL;
    writeData.Txdata = 0x86;
    spi5.transmit(writeData.data, 2);

    /*INT*/
    writeData.addr = MPU6500_INT_PIN_CFG;
    writeData.Txdata = 0x10;
    spi5.transmit(writeData.data, 2);

    writeData.addr = MPU6500_INT_ENABLE;
    writeData.Txdata = 0x01;
    spi5.transmit(writeData.data, 2);
  }

  void MPU6500::readData(uint8_t Addr, uint8_t* buffer, uint16_t length)
  {
    Addr |= 0x80;
    this->SPIx.transmit_recive(&Addr, buffer, 1, length, 0);
  }


}
