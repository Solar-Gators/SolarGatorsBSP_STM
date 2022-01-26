/*
 * FrontLights.hpp
 *
 *  Created on: Jan 17, 2022
 *      Author: John Carr
 */

#ifndef SOLARGATORSBSP_STM_DATAMODULES_INC_FRONTLIGHTS_HPP_
#define SOLARGATORSBSP_STM_DATAMODULES_INC_FRONTLIGHTS_HPP_

#include <DataModule.hpp>

namespace SolarGators {
namespace DataModules {

class FrontLights: public DataModule {
public:
  FrontLights();
  virtual ~FrontLights();
  uint16_t GetBreak() const;
  uint16_t GetThrottle() const;

protected:
  uint16_t throttle_;
  uint16_t break_;
  // TODO: Accelerometer values
};

} /* namespace DataModules */
} /* namespace SolarGators */

#endif /* SOLARGATORSBSP_STM_DATAMODULES_INC_FRONTLIGHTS_HPP_ */
