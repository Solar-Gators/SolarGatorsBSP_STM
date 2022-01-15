/*
 * UI.cpp
 *
 *  Created on: Jan 12, 2022
 *      Author: John Carr
 */

#include <UI.hpp>
#include <string>

namespace SolarGators {
namespace Drivers {

UI::UI(uint16_t background_color, HY28b& display):background_color_(background_color),display_(display)
{
  speed_ = 0;
  current_ = 0;
  state_of_charge_ = 0;
  DrawTitle(Speed_Title_Pos, "Speed");
  DrawTitle(SOC_Title_Pos, "SOC");
  DrawTitle(Current_Title_Pos, "Current");
}

UI::~UI()
{

}

void UI::UpdateSpeed(uint8_t new_speed)
{
  std::string new_speed_s = std::to_string(new_speed);
  std::string old_speed_s = std::to_string(speed_);
  display_.SetSize(Speed_Size);
  UpdateDisplayValue(Speed_Position, Speed_Char_Size, old_speed_s.c_str(), new_speed_s.c_str());
  speed_ = new_speed;
}
void UI::UpdateCurrent(uint8_t new_current)
{
  std::string new_s = std::to_string(new_current);
  std::string old_s = std::to_string(current_);
  display_.SetSize(Current_Size);
  UpdateDisplayValue(Current_Position, Current_Char_Size, old_s.c_str(), new_s.c_str());
  current_ = new_current;
}
void UI::UpdateSOC(uint8_t new_soc)
{
  std::string new_s = std::to_string(new_soc);
  std::string old_s = std::to_string(state_of_charge_);
  display_.SetSize(SOC_Size);
  UpdateDisplayValue(SOC_Position, SOC_Char_Size, old_s.c_str(), new_s.c_str());
  state_of_charge_ = new_soc;
}

void UI::UpdateDisplayValue(point_t pos, dimension_t char_size, const char* old_value, const char* new_value)
{
  // See if strings are the same
  uint8_t i = 0;
  while (*old_value && (*old_value == *new_value))
  {
    ++i;
    ++old_value;
    ++new_value;
  }
  if(*old_value == '\0')
    return;
  display_.DrawText(pos.x + i * char_size.x, pos.y, (uint8_t*)old_value, background_color_);
  if(*new_value == '\0')
  {
    new_value -= i;
    i = 0;
  }
  display_.DrawText(pos.x + i * char_size.x, pos.y, (uint8_t*)new_value, display_.RED);
}

void UI::DrawTitle(point_t pos, const char* title)
{
  display_.SetSize(Title_Size);
  display_.DrawText(pos.x, pos.y, (uint8_t*)title, title_color_);
}

} /* namespace Drivers */
} /* namespace SolarGators */
