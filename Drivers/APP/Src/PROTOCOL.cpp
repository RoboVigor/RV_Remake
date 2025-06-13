/**
* Author: Rian
* Date: 6/6/2025.
*/

#include "PROTOCOL.h"

namespace Drivers::APP
{
   PROTOCOL::PROTOCOL(ProtocolMapType protocolMap)
     :protocolMap(std::move(protocolMap))
  {

   }

  void PROTOCOL::protocolPack(uint16_t id)
   {
     if (protocolPackCallback != nullptr)
     {
       protocolPackCallback(id, this);
     }
   }

  void PROTOCOL::protocolUnpack(uint16_t id)
   {
     if (protocolUnpackCallback != nullptr)
     {
       protocolUnpackCallback(id, this);
     }
   }

  void PROTOCOL::init(void(* Pack)(uint16_t id, PROTOCOL* protocol), void(* Unpack)(uint16_t id, PROTOCOL* protocol))
   {
     this->protocolPackCallback = Pack;
     this->protocolUnpackCallback = Unpack;
   }

}