/*
 * LTC2630.hpp
 *
 *  Created on: Feb 28, 2022
 *      Author: John Carr
 */

#ifndef SOLARGATORSBSP_STM_DRIVERS_LTC2630_HPP_
#define SOLARGATORSBSP_STM_DRIVERS_LTC2630_HPP_

#include "stm32f0xx_hal.h"

namespace SolarGators {
namespace Drivers {

class LTC2630 {
  SPI_HandleTypeDef* hspi_;
  uint16_t current_val_;
  uint16_t pending_val_;
  uint8_t mode_;
  namespace Command
  {
    static constexpr uint8_t WriteData      = 0x00;
    static constexpr uint8_t UpdateOutput   = 0x01;
    static constexpr uint8_t WriteAndUpdate = 0x03;
    static constexpr uint8_t PowerDown      = 0x04;
    static constexpr uint8_t SetRefInternal = 0x06;
    static constexpr uint8_t SetRefVcc      = 0x07;
  }
  uint16_t AdjData(uint16_t data);
public:

  typedef enum class uint8_t{
    Bit8 = 0,
    Bit10 = 1,
    Bit12 = 2
  } OperatingMode;

  LTC2630(SPI_HandleTypeDef* hspi, OperatingMode mode);
  virtual ~LTC2630();
  void WriteData(uint16_t data);
  void UpdateOutput();
  void WriteAndUpdate(uint16_t data);
  void PowerDown();
  void SetRefInternal();
  void SetRefVcc();
  uint16_t GetCurrentVal() const;
};

} /* namespace Drivers */
} /* namespace SolarGators */

#endif /* SOLARGATORSBSP_STM_DRIVERS_LTC2630_HPP_ */
