/*
 * RearLights.cpp
 *
 *  Created on: Jun 17, 2022
 *      Author: John Carr
 */

#include <RearLights.hpp>

namespace SolarGators {
namespace DataModules {

namespace {
  static constexpr uint32_t ID = 0x2345;
  static constexpr uint32_t SIZE = 3;
}

RearLights::RearLights():
            DataModule(ID, 0, SIZE),
            break_(false) {
  // TODO Auto-generated constructor stub

}

RearLights::~RearLights() {
  // TODO Auto-generated destructor stub
}


bool RearLights::isBreakPressed() const
{
  return break_;
}

} /* namespace DataModules */
} /* namespace SolarGators */
