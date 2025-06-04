/**
* Author: Rian
* Date: 6/2/2025.
*/
#include "DMA.h"

#include <algorithm>

#include "stm32f4xx_ll_dma.h"

namespace Drivers::Peripherals
{
  DMA::DMA(DMAConfig dmaConfig) :
    dmaConfig(std::move(dmaConfig))
  {
  }

  void DMA::init()
  {
    switch (((uint32_t)this->dmaConfig.DMAx_Streamx & 0xFFFFFF00))
    {
    case DMA1_BASE:
      __HAL_RCC_DMA1_CLK_ENABLE();
      break;
    case DMA2_BASE:
      __HAL_RCC_DMA2_CLK_ENABLE();
      break;
    }
    DMA_HandleTypeDef dmaHandle;
    dmaHandle.Instance = this->dmaConfig.DMAx_Streamx;
    dmaHandle.Init.Channel = this->dmaConfig.Channel;
    dmaHandle.Init.Direction = this->dmaConfig.Direction;
    dmaHandle.Init.PeriphInc = this->dmaConfig.PeriphInc;
    dmaHandle.Init.MemInc = this->dmaConfig.MemInc;
    dmaHandle.Init.PeriphDataAlignment = this->dmaConfig.PeriphDataAlignment;
    dmaHandle.Init.MemDataAlignment = this->dmaConfig.MemDataAlignment;
    dmaHandle.Init.Mode = this->dmaConfig.Mode;
    dmaHandle.Init.Priority = this->dmaConfig.Priority;
    dmaHandle.Init.FIFOMode = this->dmaConfig.FIFOMode;
    dmaHandle.Init.FIFOThreshold = this->dmaConfig.FIFOThreshold;
    dmaHandle.Init.MemBurst = this->dmaConfig.MemBurst;
    dmaHandle.Init.PeriphBurst = this->dmaConfig.PeriphBurst;
    HAL_DMA_Init(&dmaHandle);

  }

  void DMA::globalInitCallback_Default()
  {

  }

  void DMA::globalInit()
  {
    globalInitCallback();
  }

  void DMA::dmaDisable()
  {
    LL_DMA_DisableStream((__LL_DMA_GET_INSTANCE(this->dmaConfig.DMAx_Streamx)),
                         (__LL_DMA_GET_STREAM(this->dmaConfig.DMAx_Streamx)));
    while (LL_DMA_IsEnabledStream((__LL_DMA_GET_INSTANCE(this->dmaConfig.DMAx_Streamx)),
                                  (__LL_DMA_GET_STREAM(this->dmaConfig.DMAx_Streamx))))
    {
    }
  }

  void DMA::dmaEnable(uint16_t length)
  {
    while (LL_DMA_IsEnabledStream((__LL_DMA_GET_INSTANCE(this->dmaConfig.DMAx_Streamx)),
                                  (__LL_DMA_GET_STREAM(this->dmaConfig.DMAx_Streamx))))
    {
    }

    switch (__LL_DMA_GET_STREAM(this->dmaConfig.DMAx_Streamx))
    {
    case LL_DMA_STREAM_0:
      LL_DMA_ClearFlag_TC0(__LL_DMA_GET_INSTANCE(this->dmaConfig.DMAx_Streamx));
      LL_DMA_ClearFlag_HT0(__LL_DMA_GET_INSTANCE(this->dmaConfig.DMAx_Streamx));
      break;

    case LL_DMA_STREAM_1:
      LL_DMA_ClearFlag_TC1(__LL_DMA_GET_INSTANCE(this->dmaConfig.DMAx_Streamx));
      LL_DMA_ClearFlag_HT1(__LL_DMA_GET_INSTANCE(this->dmaConfig.DMAx_Streamx));
      break;

    case LL_DMA_STREAM_2:
      LL_DMA_ClearFlag_TC2(__LL_DMA_GET_INSTANCE(this->dmaConfig.DMAx_Streamx));
      LL_DMA_ClearFlag_HT2(__LL_DMA_GET_INSTANCE(this->dmaConfig.DMAx_Streamx));
      break;

    case LL_DMA_STREAM_3:
      LL_DMA_ClearFlag_TC3(__LL_DMA_GET_INSTANCE(this->dmaConfig.DMAx_Streamx));
      LL_DMA_ClearFlag_HT3(__LL_DMA_GET_INSTANCE(this->dmaConfig.DMAx_Streamx));
      break;

    case LL_DMA_STREAM_4:
      LL_DMA_ClearFlag_TC4(__LL_DMA_GET_INSTANCE(this->dmaConfig.DMAx_Streamx));
      LL_DMA_ClearFlag_HT4(__LL_DMA_GET_INSTANCE(this->dmaConfig.DMAx_Streamx));
      break;

    case LL_DMA_STREAM_5:
      LL_DMA_ClearFlag_TC5(__LL_DMA_GET_INSTANCE(this->dmaConfig.DMAx_Streamx));
      LL_DMA_ClearFlag_HT5(__LL_DMA_GET_INSTANCE(this->dmaConfig.DMAx_Streamx));
      break;

    case LL_DMA_STREAM_6:
      LL_DMA_ClearFlag_TC6(__LL_DMA_GET_INSTANCE(this->dmaConfig.DMAx_Streamx));
      LL_DMA_ClearFlag_HT6(__LL_DMA_GET_INSTANCE(this->dmaConfig.DMAx_Streamx));
      break;

    case LL_DMA_STREAM_7:
      LL_DMA_ClearFlag_TC7(__LL_DMA_GET_INSTANCE(this->dmaConfig.DMAx_Streamx));
      LL_DMA_ClearFlag_HT7(__LL_DMA_GET_INSTANCE(this->dmaConfig.DMAx_Streamx));
      break;
    }

    LL_DMA_SetDataLength(__LL_DMA_GET_INSTANCE(this->dmaConfig.DMAx_Streamx),
                         __LL_DMA_GET_STREAM(this->dmaConfig.DMAx_Streamx),
                         length);

    LL_DMA_EnableStream(__LL_DMA_GET_INSTANCE(this->dmaConfig.DMAx_Streamx),
                        __LL_DMA_GET_STREAM(this->dmaConfig.DMAx_Streamx));
  }
}
