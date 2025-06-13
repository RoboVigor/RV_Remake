/**
* Author: Rian
* Date: 6/5/2025.
*/
#include "NODE.h"

#include <algorithm>

namespace Drivers::APP
{
   NODE::NODE(NodeInfo nodeInfo)
     :nodeInfo(std::move(nodeInfo))
  {  }

}