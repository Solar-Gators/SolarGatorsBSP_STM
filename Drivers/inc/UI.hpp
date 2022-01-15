/*
 * UI.h
 *
 *  Created on: Jan 12, 2022
 *      Author: John Carr
 */

#ifndef SOLARGATORSBSP_DRIVERS_INC_UI_HPP_
#define SOLARGATORSBSP_DRIVERS_INC_UI_HPP_

#include "main.h"
// TODO: Make this a generic display driver
#include "HY28b.hpp"

namespace SolarGators {
namespace Drivers {

class UI {
public:
  UI(uint16_t background_color_, HY28b& display);
  virtual ~UI();
  void UpdateSpeed(uint8_t);
  void UpdateCurrent(uint8_t);
  void UpdateSOC(uint8_t);
private:
  void UpdateDisplayValue(point_t pos, dimension_t char_size, const char* old_value, const char* new_value);
  void DrawTitle(point_t pos, const char* title);
  // Background Color
  const uint16_t background_color_;
  const uint16_t title_color_ = HY28b::WHITE;
  // Display driver handle
  HY28b& display_;
  // Max Digits
  static constexpr uint8_t Max_Current_Digits = 3;
  static constexpr uint8_t Max_Speed_Digits = 2;
  static constexpr uint8_t Max_SOC_Digits = 3;
  /* ---- Important ---- */
  // This is the max of all the above
  static constexpr uint8_t Max_Length = 3;
  // Sizes
  inline static constexpr uint8_t Current_Size = 4;
  inline static constexpr uint8_t Speed_Size = 5;
  inline static constexpr uint8_t SOC_Size = 4;
  inline static constexpr uint8_t Title_Size = 1;
  // Char Size (Defined in ASCII.hpp)
  inline static constexpr dimension_t Char_Size = {
      .x = 8,
      .y = 16
  };
  inline static constexpr dimension_t Current_Char_Size =
  {
      .x = Char_Size.x * Current_Size,
      .y = Char_Size.y * Current_Size
  };
  inline static constexpr dimension_t Speed_Char_Size =
  {
      .x = Char_Size.x * Speed_Size,
      .y = Char_Size.y * Speed_Size
  };
  inline static constexpr dimension_t SOC_Char_Size =
  {
      .x = Char_Size.x * SOC_Size,
      .y = Char_Size.y * SOC_Size
  };
  inline static constexpr dimension_t Title_Char_Size =
  {
      .x = Char_Size.x * Title_Size,
      .y = Char_Size.y * Title_Size
  };
  // Positions
  inline static constexpr point_t Speed_Position =
  {
    .x = HY28b::MAX_SCREEN_X/2 - (Speed_Char_Size.x * Max_Speed_Digits)/2,
    .y = HY28b::MAX_SCREEN_Y/2 - (Speed_Char_Size.y)/2
  };
  inline static constexpr point_t Current_Position =
  {
    .x = (HY28b::MAX_SCREEN_X/4)*3 - (Current_Char_Size.x * Max_Current_Digits)/2,
    .y = HY28b::MAX_SCREEN_Y/4 - (Current_Char_Size.y)/2
  };
  inline static constexpr point_t SOC_Position =
  {
    .x = HY28b::MAX_SCREEN_X/4 - (SOC_Char_Size.x * Max_SOC_Digits)/2,
    .y = HY28b::MAX_SCREEN_Y/4 - (SOC_Char_Size.y)/2
  };
  inline static constexpr point_t Speed_Title_Pos =
  {
      .x = Speed_Position.x + Speed_Char_Size.x/2,
      .y = Speed_Position.y - 10
  };
  inline static constexpr point_t Current_Title_Pos =
  {
      .x = Current_Position.x + Current_Char_Size.x/2*Max_Current_Digits - 20,
      .y = Current_Position.y - 10
  };
  inline static constexpr point_t SOC_Title_Pos =
  {
      .x = SOC_Position.x + SOC_Char_Size.x/2*Max_SOC_Digits - 5,
      .y = SOC_Position.y - 10
  };
  // Display values
  uint8_t speed_;
  uint8_t current_;
  uint8_t state_of_charge_;
};

} /* namespace Drivers */
} /* namespace SolarGators */

#endif /* SOLARGATORSBSP_DRIVERS_INC_UI_HPP_ */
