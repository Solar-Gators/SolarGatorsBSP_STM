/*
 * UI.cpp
 *
 *  Created on: Jan 12, 2022
 *      Author: John Carr
 */

#include <UI.hpp>

namespace SolarGators {
namespace Drivers {

void InfoSquare::Draw(ILI9341& disp)
{
  disp.SetTextSize(TextSize);
  // Draw the Border
  disp.DrawRect(x, y, DataSqW, DataSqH, UI::color_neutral_);
  // Draw the Title
  disp.DrawText(x+TextPaddX, y+TitlePaddY, title.c_str(), UI::color_neutral_);
  etl::string<5> tmp(" N/A ");
  UpdateValue(disp, tmp);
}

void InfoSquare::UpdateValue(ILI9341& disp, etl::string<5>& val)
{
  disp.SetTextSize(TextSize);
  disp.DrawText(x+TextPaddX, TextHeight*TextSize+TitlePaddY+DataPaddY+y, val.c_str(), UI::color_neutral_);
}

UI::UI(ILI9341& display):disp(display)
{
  // Set Screen Orientation
  disp.SetRotation(3);
  // Set Background Color
  disp.ClearScreen(0x0000);
  // Setup info squares
  etl::string<5> titles[] = {"Accel"," SOC ","Voltg","Curnt"};
  for (size_t i = 0; i < first_row_.size(); ++i)
  {
    first_row_[i].title = titles[i];
    first_row_[i].x = i*InfoSquare::DataSqW;
    first_row_[i].y = 0;
    first_row_[i].Draw(disp);
  }
  DrawSpeed();
  DrawTripCodes();
}

UI::~UI()
{

}

void UI::UpdateSquare(uint8_t num, etl::string<5>& val)
{
  if(num < 4)
  {
    first_row_[num].UpdateValue(disp, val);
  }
}

void UI::DrawSpeed()
{
  // Draw Speed
  disp.SetTextSize(3);
  const char* str2 = "Speed";
  disp.DrawText(115, 54, str2, color_neutral_);
  disp.SetTextSize(4);
  UpdateSpeed(99.9);
}

void UI::UpdateSpeed(float speed)
{
  // Draw Speed
  disp.SetTextSize(3);
  etl::string<4> s_speed;
  etl::to_string(speed, s_speed, etl::format_spec().precision(1).width(4).fill(0), false);
  disp.DrawText(112+9, 82, s_speed.c_str(), color_neutral_);
}

void UI::DrawTripCodes()
{
  // Mitsuba Trip Codes
  const char* mitsuba_faults[] = {
    "AD Sensor Error", "Motor Curr Sensor U Error",
    "Motor Curr Sensor W Error", "Fet Therm Error",
    "Batt Volt Sensor Error", "Batt Curr Sensor Error",
    "Batt Curr Sensor Adj Error", "Motor Curr Sensor Adj Error",
    "Accel Pos Error", "Cont Volt Sensor Error",
    "Power System Error", "Over Curr Error",
    "Over Volt Error", "Over Curr Limit",
    "Motor System Error", "Motor Lock",
    "Hall Sensor Short", "Hall Sensor Open" };
  // BMS Trip Codes
  const char* orion_faults[] = {
    "Internal Cell Communication", "Cell Balancing Stuck Off",
    "Weak Cell", "Low Cell Voltage", "Cell Open Wiring",
    "Current Sensor", "Cell Voltage Over 5v",
    "Cell Bank", "Weak Pack", "Fan Monitor",
    "Thermistor", "Can Communication",
    "Redundant Power Supply", "High Voltage Isolation",
    "Invalid Input Supply Voltage", "Charge En Relay",
    "Discharge En Relay", "Charger Safety Relay",
    "Internal Hardware", "Internal Heatsink Thermistor",
    "Internal Logic", "Highest Cell Voltage Too High",
    "Lowest Cell Voltage Too Low", "Pack Too Hot"};
    disp.SetTextSize(2);
    disp.DrawText(0, 120, "BMS Status: ", color_neutral_);
    disp.DrawText(2*6*12, 120, "OK", color_ok_);
    // if there is a failure
    if(false) // TODO JC make this actually work
    {
      disp.DrawText(0, 140, orion_faults[3], color_neutral_);
    }
    disp.DrawText(0, 180, "MC Status: ", color_neutral_);
    disp.DrawText(2*6*11, 180, "Trip", color_fail_);
    // if there is a failure
    if(true) // TODO JC make this actually work
    {
      disp.DrawText(0, 200, mitsuba_faults[1], color_fail_);
    }
}

} /* namespace Drivers */
} /* namespace SolarGators */
