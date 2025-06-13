/**
* Author: Rian
* Date: 6/5/2025.
*/
#include "BRIDGE.h"

namespace Drivers::APP
{
   BRIDGE::BRIDGE(BridgeInfo bridgeInfo)
  :bridgeInfo(std::move(bridgeInfo)){  }

  void BRIDGE::bridgeSend(uint16_t id)
   {
     if (bridgeSendCallback != nullptr)
     {
       bridgeSendCallback(id, this);
     }
   }

  void BRIDGE::bridgeReceive(uint16_t id)
   {
     if (bridgeReceiveCallback != nullptr)
     {
       bridgeSendCallback(id, this);
     }
   }

  void BRIDGE::init(void (*Send)(uint16_t id, BRIDGE* bridge), void (*Receive)(uint16_t id, BRIDGE* bridge))
   {
     this->bridgeSendCallback = Send;
     this->bridgeReceiveCallback = Receive;
   }

}