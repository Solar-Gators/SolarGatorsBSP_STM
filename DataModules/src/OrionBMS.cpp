/*
 * OrionBMS.cpp
 *
 *  Created on: Jan 14, 2022
 *      Author: John Carr
 */

#include "OrionBMS.hpp"

namespace SolarGators::DataModules
{
  OrionBMS::OrionBMS(uint32_t id):
      DataModule(id, Size)
  { }

  OrionBMS::~OrionBMS()
  { }

  float OrionBMS::GetLowCellVoltage()
  {
    return lowCellVoltage;
  }
  float OrionBMS::GetHighCellVoltage()
  {
    return highCellVoltage;
  }
  float OrionBMS::GetAvgCellVoltage()
  {
    return avgCellVoltage;
  }
  float OrionBMS::GetPackVoltage()
  {
    return packSummedVoltage;
  }
  float OrionBMS::GetStateOfCharge()
  {
    // TODO: Add this to BMS packet
    return 0;
  }
  void OrionBMS::ToByteArray(uint8_t* buff) const
  {
    float convLowCellVoltage = lowCellVoltage * 10000;
    float convHighCellVoltage = highCellVoltage * 10000;
    float convAvgCellVoltage = avgCellVoltage * 10000;
    float convPackSummedVoltage = packSummedVoltage * 1000;

    buff[0] = static_cast<uint32_t>(convLowCellVoltage) & 0xFF;
    buff[1] = (static_cast<uint32_t>(convLowCellVoltage) >> 8) & 0xFF;
    buff[2] = static_cast<uint32_t>(convHighCellVoltage) & 0xFF;
    buff[3] = (static_cast<uint32_t>(convHighCellVoltage) >> 8) & 0xFF;
    buff[4] = static_cast<uint32_t>(convAvgCellVoltage) & 0xFF;
    buff[5] = (static_cast<uint32_t>(convAvgCellVoltage) >> 8) & 0xFF;
    buff[6] = static_cast<uint32_t>(convPackSummedVoltage) & 0xFF;
    buff[7] = (static_cast<uint32_t>(convPackSummedVoltage) >> 8) & 0xFF;
  }

  void OrionBMS::FromByteArray(uint8_t* buff)
  {
    uint32_t preLCV = (static_cast<uint32_t>(buff[1]) << 8) | buff[0];
    uint32_t preHCV = (static_cast<uint32_t>(buff[3]) << 8) | buff[2];
    uint32_t preACV = (static_cast<uint32_t>(buff[5]) << 8) | buff[4];
    uint32_t prePCV = (static_cast<uint32_t>(buff[7]) << 8) | buff[6];
    lowCellVoltage = static_cast<float>(preLCV)/10000;
    highCellVoltage = static_cast<float>(preHCV)/10000;
    avgCellVoltage = static_cast<float>(preACV)/10000;
    //TODO: figure out whether this should be 1000 or 100
    packSummedVoltage = static_cast<float>(prePCV)/1000;
  }
}
