/**
* Author: Rian
* Date: 6/2/2025.
*/
#include "TIM.h"

#include <algorithm>

#include "stm32f4xx_ll_tim.h"

namespace Drivers::Peripherals
{
  TIM::TIM(BaseConfig baseConfig, OCConfig ocConfig)
    :baseConfig(std::move(baseConfig)), ocConfig(std::move(ocConfig))
  {
  }

  void TIM::PWMInit()
  {
    TIM_HandleTypeDef timHandle;
    timHandle.Instance = this->baseConfig.TIMx;
    timHandle.Init.Prescaler = this->baseConfig.Prescaler;
    timHandle.Init.CounterMode = this->baseConfig.CounterMode;
    timHandle.Init.Period = this->baseConfig.Period;
    timHandle.Init.ClockDivision = this->baseConfig.ClockDivision;
    timHandle.Init.RepetitionCounter = this->baseConfig.RepetitionCounter;
    timHandle.Init.AutoReloadPreload = this->baseConfig.AutoReloadPreload;
    HAL_TIM_PWM_Init(&timHandle);
    if (this->baseConfig.interruptFlag != 0)
    {
      __HAL_TIM_ENABLE_IT(&timHandle, this->baseConfig.interruptFlag);
    }
    this->timHandle = timHandle;
  }

  void TIM::PWMConfig(uint32_t channel)
  {
    TIM_OC_InitTypeDef ocHandle;
    ocHandle.OCMode = this->ocConfig.OCMode;
    ocHandle.OCFastMode = this->ocConfig.OCFastMode;
    ocHandle.Pulse = this->ocConfig.Pulse;
    ocHandle.OCPolarity = this->ocConfig.OCPolarity;
    ocHandle.OCNPolarity = this->ocConfig.OCNPolarity;
    ocHandle.OCIdleState = this->ocConfig.OCIdleState;
    ocHandle.OCNIdleState = this->ocConfig.OCNIdleState;
    HAL_TIM_PWM_ConfigChannel(&this->timHandle, &ocHandle, channel);
  }

  void TIM::globalInitCallBack_Default()
  {
  }

  void TIM::globalInit()
  {
    globalInitCallback();
  }

  void TIM::setDuty(uint32_t channel, uint8_t duty)
  {
    uint32_t CCR = this->baseConfig.Period * duty / 100;
    switch (channel)
    {
    case TIM_CHANNEL_1:
      LL_TIM_OC_SetCompareCH1(this->baseConfig.TIMx, CCR);
      break;

    case TIM_CHANNEL_2:
      LL_TIM_OC_SetCompareCH2(this->baseConfig.TIMx, CCR);
      break;

    case TIM_CHANNEL_3:
      LL_TIM_OC_SetCompareCH3(this->baseConfig.TIMx, CCR);
      break;

    case TIM_CHANNEL_4:
      LL_TIM_OC_SetCompareCH4(this->baseConfig.TIMx, CCR);
      break;

    }
  }

  void TIM::PWMStart(uint32_t channel)
  {
    HAL_TIM_PWM_Start(&this->timHandle, channel);
  }


}
