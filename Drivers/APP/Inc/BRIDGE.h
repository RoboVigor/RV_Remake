/**
* Author: Rian
* Date: 6/5/2025.
*/

#ifndef BRIDGE_H
#define BRIDGE_H
#include "PROTOCOL.h"
#include "stm32f4xx_hal.h"

namespace Drivers::APP
{
  class BRIDGE
  {
  public:
    struct BridgeInfo
    {
      PROTOCOL* protocol;
    };

    BridgeInfo bridgeInfo;

    explicit BRIDGE(BridgeInfo bridgeInfo);

    void bridgeSend(uint16_t id);
    void bridgeReceive(uint16_t id);

    void (*bridgeSendCallback) (uint16_t id, BRIDGE* bridge);
    void (*bridgeReceiveCallback) (uint16_t id, BRIDGE* bridge);

    void init(
      void (*Send)(uint16_t id, BRIDGE* bridge),
      void (*Receive)(uint16_t id, BRIDGE* bridge));
  };
}

#endif //BRIDGE_H
