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
  disp.DrawRect(x, y, DataSqW, DataSqH, 0xF800);
  // Draw the Title
  disp.DrawText(x+TextPaddX, y+TitlePaddY, title.c_str(), 0xF800);
  UpdateValue(disp, " N/A ");
}

void InfoSquare::UpdateValue(ILI9341& disp, etl::string<5> val)
{
  disp.DrawText(x+TextPaddX, TextHeight*TextSize+TitlePaddY+DataPaddY+y, val.c_str(), 0xF800);
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

void UI::UpdateSquare(uint8_t num, etl::string<5> val)
{

}

void UI::DrawSpeed()
{
  // Draw Speed
  disp.SetTextSize(3);
  const char* str2 = "Speed";
  disp.DrawText(115, 54, str2, 0xF800);
  disp.SetTextSize(4);
  UpdateSpeed(99.9);
}

void UI::UpdateSpeed(float speed)
{
  etl::string<4> s_speed;
  etl::to_string(speed, s_speed, etl::format_spec().precision(1).width(4).fill(0), false);
  disp.DrawText(112, 82, s_speed.c_str(), 0xF800);
}

void UI::DrawTripCodes()
{
  // Mitsuba Trip Codes
  const char* mitsuba_faults[] = {
    "adSensorError", "motorCurrSensorUError",
    "motorCurrSensorWError", "fetThermError",
    "battVoltSensorError", "battCurrSensorError",
    "battCurrSensorAdjError", "motorCurrSensorAdjError",
    "accelPosError", "contVoltSensorError",
    "powerSystemError", "overCurrError",
    "overVoltError", "overCurrLimit",
    "motorSystemError", "motorLock",
    "hallSensorShort", "hallSensorOpen" };
  // BMS Trip Codes
  const char* orion_faults[] = {
    "Internal Cell Communication",  
    "Cell Balancing Stuck Off",
    "Weak Cell",    
    "Low Cell Voltage",             
    "Cell Open Wiring",
    "Current Sensor",
    "Cell Voltage Over 5v",         
    "Cell Bank",
    "Weak Pack",
    "Fan Monitor",
    "Thermistor",
    "Can Communication",            
    "Redundant Power Supply",
    "High Voltage Isolation",
    "Invalid Input Supply Voltage",
    "Charge En Relay",
    "Discharge En Relay",
    "Charger Safety Relay",
    "Internal Hardware",
    "Internal Heatsink Thermistor",
    "Internal Logic",
    "Highest Cell Voltage Too High",
    "Lowest Cell Voltage Too Low",
    "Pack Too Hot"};

}

} /* namespace Drivers */
} /* namespace SolarGators */
