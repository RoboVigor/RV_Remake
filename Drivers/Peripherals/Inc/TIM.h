//
// Created by Admin on 5/26/2025.
//

#ifndef TIM_H
#define TIM_H
#include "stm32f4xx_hal.h"

namespace Drivers::Peripherals
{
  class TIM
  {
  private:
    struct BaseConfig
    {
      TIM_TypeDef* TIMx;
      uint32_t Prescaler;
      uint32_t CounterMode = TIM_COUNTERMODE_UP;
      uint32_t Period;
      uint32_t ClockDivision = TIM_CLOCKDIVISION_DIV1;
      uint32_t RepetitionCounter = 0x00;
      uint32_t AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
      uint32_t interruptFlag;
    };
    struct OCConfig
    {
      uint32_t OCMode = TIM_OCMODE_PWM1;
      uint32_t Pulse;
      uint32_t OCPolarity = TIM_OCPOLARITY_HIGH;
      uint32_t OCNPolarity;
      uint32_t OCFastMode = TIM_OCFAST_DISABLE;
      uint32_t OCIdleState = TIM_OCIDLESTATE_RESET;
      uint32_t OCNIdleState;
    };

    BaseConfig baseConfig;
    OCConfig ocConfig;

    TIM_HandleTypeDef timHandle;

    void PWMInit();
    void PWMConfig(uint32_t channel);
    static void globalInitCallBack_Default();
    void setDuty(uint32_t channel, uint8_t duty);
    void PWMStart(uint32_t channel);

  public:
    TIM(BaseConfig baseConfig, OCConfig ocConfig);
    static void globalInit();
    static inline void (*globalInitCallback)() = globalInitCallBack_Default;
  };
}
#endif //TIM_H
