/**
 * Author: Rian
 * Date: 6/24/2025.
 */
#include "GYROSCOPE.h"

#include <algorithm>

namespace Drivers::APP
{
  GYROSCOPE::GYROSCOPE(GyroscopeInfo gyroscopeInfo) : gyroscopeInfo(std::move(gyroscopeInfo)) {}

  void GYROSCOPE::gyroscopeUpdate()
  {
    gyroscopeUpdateCallback(this);
  }



} // namespace Drivers::APP
