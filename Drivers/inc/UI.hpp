/*
 * UI.h
 *
 *  Created on: Jan 12, 2022
 *      Author: John Carr
 */

#ifndef SOLARGATORSBSP_DRIVERS_INC_UI_HPP_
#define SOLARGATORSBSP_DRIVERS_INC_UI_HPP_

#include "main.h"
#include "ILI9341.hpp"

// ETL Stuff
#include "etl/array.h"
#include "etl/string.h"
#include "etl/to_string.h"
#include "etl/string_utilities.h"
#include "etl/format_spec.h"

// RTOS Stuff
#include <cmsis_os.h>

namespace SolarGators {
namespace Drivers {

// Minor UI Element Struct
class InfoSquare {
public:
  etl::string<5> title;
  uint16_t x;
  uint16_t y;
  static constexpr uint16_t TextPaddX  = 10;
  static constexpr uint16_t TitlePaddY = 7;
  static constexpr uint16_t DataPaddY  = 4;
  static constexpr uint16_t DataSqW    = 80;
  static constexpr uint16_t DataSqH    = 50;
  static constexpr uint16_t TextWidth  = 6;
  static constexpr uint16_t TextHeight = 8;
  static constexpr uint8_t TextSize = 2;
  void Draw(ILI9341& disp);
  void UpdateValue(ILI9341& disp, etl::string<5> val);
};

// Trip Code Struct

class UI {
public:
  UI(ILI9341& display);
  ~UI();
  void Update();
  ILI9341& disp;
  void UpdateSquare(uint8_t num, etl::string<5> val);
  void UpdateSpeed(float speed);
private:
  etl::array<InfoSquare, 4> first_row_;
  void DrawSpeed();
  void DrawTripCodes();
};

} /* namespace Drivers */
} /* namespace SolarGators */

#endif /* SOLARGATORSBSP_DRIVERS_INC_UI_HPP_ */
