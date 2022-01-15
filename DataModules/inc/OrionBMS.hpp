/*
 * OrionBMS.hpp
 *
 *  Created on: Jan 14, 2022
 *      Author: John Carr
 */

#ifndef SOLARGATORSBSP_DATAMODULES_INC_ORIONBMS_HPP_
#define SOLARGATORSBSP_DATAMODULES_INC_ORIONBMS_HPP_

#include <DataModule.hpp>

namespace SolarGators::DataModules
{
  class OrionBMS final: public DataModule
  {
  public:
    OrionBMS(uint32_t id);
    ~OrionBMS();
    float GetLowCellVoltage();
    float GetHighCellVoltage();
    float GetAvgCellVoltage();
    float GetPackVoltage();
    float GetStateOfCharge();
    void ToByteArray(uint8_t* buff) const;
    void FromByteArray(uint8_t* buff);
    static constexpr uint8_t Size = 8;
  protected:
    float lowCellVoltage;
    float highCellVoltage;
    float avgCellVoltage;
    float packSummedVoltage;
  };
}

#endif /* SOLARGATORSBSP_DATAMODULES_INC_ORIONBMS_HPP_ */
