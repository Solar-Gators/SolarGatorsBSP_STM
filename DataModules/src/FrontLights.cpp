/*
 * FrontLights.cpp
 *
 *  Created on: Jan 17, 2022
 *      Author: John Carr
 */

#include <FrontLights.hpp>

namespace SolarGators {
namespace DataModules {
namespace {
  static constexpr uint32_t ID = 0x1234;
  static constexpr uint32_t SIZE = 0x2;
}

FrontLights::FrontLights():
        DataModule(ID, 0, SIZE)
{
  // TODO Auto-generated constructor stub

}

FrontLights::~FrontLights()
{
  // TODO Auto-generated destructor stub
}

uint16_t FrontLights::GetBreak() const
{
  return break_;
}

uint16_t FrontLights::GetThrottle() const
{
  return throttle_;
}

} /* namespace DataModules */
} /* namespace SolarGators */
