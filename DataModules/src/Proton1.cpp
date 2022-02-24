/*
 * Proton1.cpp
 *
 *  Created on: Jan 14, 2022
 *      Author: John Carr
 */

#include <Proton1.hpp>

namespace SolarGators {
namespace DataModules {

static constexpr uint8_t Mppt_Size = 8;

Proton1::Proton1(uint32_t id):
    DataModule(id, 0, Mppt_Size), arrayVoltage(0),
    arrayCurrent(0), batteryVoltage(0),mpptTemperature(0)
{ }

Proton1::~Proton1()
{ }

void Proton1::ToByteArray(uint8_t* buff) const
{
  float convArrayVoltage = arrayVoltage * 100;
  float convArrayCurrent = arrayCurrent * 100;
  float convBatteryVoltage = batteryVoltage * 100;
  float convMpptTemperature = mpptTemperature * 100;

  buff[0] = static_cast<uint32_t>(convArrayVoltage) & 0xFF;
  buff[1] = (static_cast<uint32_t>(convArrayVoltage) >> 8) & 0xFF;
  buff[2] = static_cast<uint32_t>(convArrayCurrent) & 0xFF;
  buff[3] = (static_cast<uint32_t>(convArrayCurrent) >> 8) & 0xFF;
  buff[4] = static_cast<uint32_t>(convBatteryVoltage) & 0xFF;
  buff[5] = (static_cast<uint32_t>(convBatteryVoltage) >> 8) & 0xFF;
  buff[6] = static_cast<uint32_t>(convMpptTemperature) & 0xFF;
  buff[7] = (static_cast<uint32_t>(convMpptTemperature) >> 8) & 0xFF;
}

void Proton1::FromByteArray(uint8_t* buff)
{
  uint32_t preArrayVoltage = (static_cast<uint32_t>(buff[1]) << 8) | buff[0];
  uint32_t preArrayCurrent = (static_cast<uint32_t>(buff[3]) << 8) | buff[2];
  uint32_t preBatteryVoltage = (static_cast<uint32_t>(buff[5]) << 8) | buff[4];
  uint32_t preMpptTemperature = (static_cast<uint32_t>(buff[7]) << 8) | buff[6];
  arrayVoltage = static_cast<float>(preArrayVoltage)/100;
  arrayCurrent = static_cast<float>(preArrayCurrent)/100;
  batteryVoltage = static_cast<float>(preBatteryVoltage)/100;
  mpptTemperature = static_cast<float>(preMpptTemperature)/100;
}

} /* namespace DataModules */
} /* namespace SolarGators */
