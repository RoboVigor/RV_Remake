/**
* Author: Rian
* Date: 6/5/2025.
*/

#ifndef NODE_H
#define NODE_H
#include "stm32f4xx_hal.h"
#include "ProtocolDataConfig.h"

namespace Drivers::APP
{
  class NODE
  {
  public:
    struct NodeInfo
    {
      void *peripheralObj;
      PeripheralType peripheralType;
      uint8_t state;

      uint8_t sendBuffer[128];
      uint8_t receiveBuffer[128];
    };

    NodeInfo nodeInfo;

    explicit NODE(NodeInfo nodeInfo);

  };
}
#endif //NODE_H
