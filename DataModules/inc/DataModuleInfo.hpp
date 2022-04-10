/*
 * DataModuleInfo.hpp
 *
 *  Created on: Jan 14, 2022
 *      Author: John Carr
 */

#ifndef SOLARGATORSBSP_DATAMODULES_INC_DATAMODULEINFO_HPP_
#define SOLARGATORSBSP_DATAMODULES_INC_DATAMODULEINFO_HPP_


namespace SolarGators::DataModuleInfo
{
// ---- Addresses ---- //

// BMS
static constexpr uint32_t BMS_RX0_MSG_ID = 0x6B0;
static constexpr uint32_t BMS_RX1_MSG_ID = 0x6B1;
static constexpr uint32_t BMS_RX2_MSG_ID = 0x6B2;
static constexpr uint32_t BMS_RX3_MSG_ID = 0x6B3;
static constexpr uint32_t BMS_RX4_MSG_ID = 0x6B4;
static constexpr uint32_t BMS_RX5_MSG_ID = 0x6B5;

// Mitsuba
//TX Messages
static constexpr uint32_t MOTORTX_RL_MSG_ID = 0x08F89540;
//RX Messages
static constexpr uint32_t MOTORRX0_RL_MSG_ID = 0x08850225;
static constexpr uint32_t MOTORRX1_RL_MSG_ID = 0x08950225;
static constexpr uint32_t MOTORRX2_RL_MSG_ID = 0x08A50225;

// MPPT
static constexpr uint16_t MPPT0_MSG_ID = 0x600;

// Steering Wheel
static constexpr uint16_t STEERING_ID = 2048;

// Front Lights
static constexpr uint16_t FRONT_LIGHTS_ID = 2049;

// Rear Lights
static constexpr uint16_t REAR_LIGHTS_ID = 2050;

}


#endif /* SOLARGATORSBSP_DATAMODULES_INC_DATAMODULEINFO_HPP_ */
