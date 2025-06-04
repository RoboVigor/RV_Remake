//
// Created by Admin on 5/26/2025.
//

#ifndef DMA_H
#define DMA_H
#include "stm32f4xx_hal.h"

namespace Drivers::Peripherals
{
  class DMA
  {
  public:
    struct DMAConfig
    {
      DMA_Stream_TypeDef* DMAx_Streamx;
      uint32_t Channel;
      uint32_t Direction;
      uint32_t PeriphInc;
      uint32_t MemInc;
      uint32_t PeriphDataAlignment;
      uint32_t MemDataAlignment;
      uint32_t Mode;
      uint32_t Priority;
      uint32_t FIFOMode;
      uint32_t FIFOThreshold;
      uint32_t MemBurst;
      uint32_t PeriphBurst;
      uint32_t interruptFlag;
    };
  private:
    DMAConfig dmaConfig;
    static void globalInitCallback_Default();

  public:
    explicit DMA(DMAConfig dmaConfig);
    void init();
    static void globalInit();
    static inline void (* globalInitCallback)() = globalInitCallback_Default;
    void dmaDisable();
    void dmaEnable(uint16_t length);
  };
}
#endif //DMA_H
