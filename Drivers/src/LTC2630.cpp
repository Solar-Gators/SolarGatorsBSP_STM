/*
 * LTC2630.cpp
 *
 *  Created on: Feb 28, 2022
 *      Author: John Carr
 */

#include "LTC2630.hpp"

namespace SolarGators {
namespace Drivers {

LTC2630::LTC2630(SPI_HandleTypeDef* hspi, OperatingMode mode):hspi_(hspi),mode_(mode),current_val_(0)
{
  WriteAndUpdate(0x00);
}

LTC2630::~LTC2630()
{
  // If it falls out of scope we don't wana be stuck accelerating
  WriteAndUpdate(0x00);
}

void LTC2630::WriteData(uint16_t data)
{
  pending_val_ = data;
  data = AdjData(data);
  uint8_t buff[3] = { Command::WriteData << 4, data & 0xff, data >> 8 };
  HAL_SPI_Transmit(hspi_, &buff, 3, HAL_MAX_DELAY);
}
void LTC2630::UpdateOutput()
{
  uint16_t data = 0x0000;
  uint8_t buff[3]={ Command::UpdateOutput << 4, data & 0xff, data >> 8 };
  HAL_SPI_Transmit(hspi_, &buff, 3, HAL_MAX_DELAY);
  current_val_ = pending_val_;
}
void LTC2630::WriteAndUpdate(uint16_t data)
{
  current_val_ = data;
  data = AdjData(data);
  uint8_t buff[3]={ Command::WriteAndUpdate << 4, data & 0xff, data >> 8 };
  HAL_SPI_Transmit(hspi_, &buff, 3, HAL_MAX_DELAY);
}
void LTC2630::PowerDown()
{
  uint16_t data = 0x0000;
  uint8_t buff[3]={ Command::PowerDown << 4, data & 0xff, data >> 8 };
  HAL_SPI_Transmit(hspi_, &buff, 3, HAL_MAX_DELAY);
}
void LTC2630::SetRefInternal()
{
  uint16_t data = 0x0000;
  uint8_t buff[3]={ Command::SetRefInternal << 4, data & 0xff, data >> 8 };
  HAL_SPI_Transmit(hspi_, &buff, 3, HAL_MAX_DELAY);
}
void LTC2630::SetRefVcc()
{
  uint16_t data = 0x0000;
  uint8_t buff[3]={ Command::SetRefVcc << 4, data & 0xff, data >> 8 };
  HAL_SPI_Transmit(hspi_, &buff, 3, HAL_MAX_DELAY);
}

uint16_t LTC2630::AdjData(uint16_t data)
{

  switch (mode_) {
    case OperatingMode::Bit8:
      return data << 8;
    case OperatingMode::Bit10:
      return data << 6;
    case OperatingMode::Bit12:
      return data << 4;
    default:
      return 0;  // Fail Safe
  }
}

} /* namespace Drivers */
} /* namespace SolarGators */
