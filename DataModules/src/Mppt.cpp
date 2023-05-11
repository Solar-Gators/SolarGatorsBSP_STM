/*
 * MPPT.cpp
 *
 *  Created on: Apr 17, 2023
 *      Author: Jack W
 */
#include <Mppt.hpp>
#include <string.h>

namespace {
	static constexpr uint32_t SIZE = 8;
}

namespace SolarGators::DataModules
{
Mpptx0::Mpptx0(uint32_t can_id):
		DataModule(can_id, 0, SIZE),
		inputVoltage(0),
		inputCurrent(0) // unsure if i need to do this, orionBMS doesnt but steering does
		{}

void Mpptx0::ToByteArray(uint8_t* buff) const
{
uint8_t hold_Volt[sizeof(float)];
uint8_t hold_Cur[sizeof(float)];

memcpy(hold_Volt, &inputVoltage, sizeof(float));
memcpy(hold_Cur, &inputCurrent, sizeof(float));

	for (int i=0;i<=3;i++){
		buff[i] = hold_Volt[i];
	}
	for (int i=4;i<=7;i++){
		buff[i] = hold_Cur[i];
	}
}

void Mpptx0::FromByteArray(uint8_t* buff)
{
uint8_t hold_Volt[sizeof(float)];
uint8_t hold_Cur[sizeof(float)];

	for(int i=0;i<=3;i++){
		hold_Volt[i] = buff[i];
	}
	for(int i=4;i<=7;i++){
		hold_Cur[i] = buff[i];
	}
memcpy(&inputVoltage, hold_Volt, sizeof(float));
memcpy(&inputCurrent, hold_Cur, sizeof(float));
}

float Mpptx0::getInputVoltage() const {
	return inputVoltage;
}

float Mpptx0::getInputCurrent() const {
	return inputCurrent;
}

Mpptx1::Mpptx1(uint32_t can_id): // INCREMENT BY 1 FROM MPPTx0
		DataModule(can_id, 0, SIZE),
		outputVoltage(0),
		outputCurrent(0) // unsure if i need to do this, orionBMS doesnt but steering does
{}

void Mpptx1::ToByteArray(uint8_t* buff) const
{
uint8_t hold_Volt[sizeof(float)];
uint8_t hold_Cur[sizeof(float)];

memcpy(hold_Volt, &outputVoltage, sizeof(float));
memcpy(hold_Cur, &outputCurrent, sizeof(float));

	for (int i=0;i<=3;i++){
		buff[i] = hold_Volt[i];
	}
	for (int i=4;i<=7;i++){
		buff[i] = hold_Cur[i];
	}
}

void Mpptx1::FromByteArray(uint8_t* buff)
{
uint8_t hold_Volt[sizeof(float)];
uint8_t hold_Cur[sizeof(float)];

	for(int i=0;i<=3;i++){
		hold_Volt[i] = buff[i];
	}
	for(int i=4;i<=7;i++){
		hold_Cur[i] = buff[i];
	}
memcpy(&outputVoltage, hold_Volt, sizeof(float));
memcpy(&outputCurrent, hold_Cur, sizeof(float));
}

float Mpptx1::getOutputVoltage() const {
	return outputVoltage;
}

float Mpptx1::getOutputCurrent() const {
	return outputCurrent;
}

Mpptx2::Mpptx2(uint32_t can_id): // INCREMENT BY 2 FROM MPPTx0
	DataModule(can_id, 0, SIZE),
	mosfetTemp(0),
	controllerTemp(0) // unsure if i need to do this, orionBMS doesnt but steering does
{}

void Mpptx2::ToByteArray(uint8_t* buff) const
{
uint8_t hold_Mos[sizeof(float)];
uint8_t hold_Con[sizeof(float)];

memcpy(hold_Mos, &mosfetTemp, sizeof(float));
memcpy(hold_Con, &controllerTemp, sizeof(float));

	for (int i=0;i<=3;i++){
		buff[i] = hold_Mos[i];
	}
	for (int i=4;i<=7;i++){
		buff[i] = hold_Con[i];
	}
}

void Mpptx2::FromByteArray(uint8_t* buff)
{
uint8_t hold_Mos[sizeof(float)];
uint8_t hold_Con[sizeof(float)];

	for(int i=0;i<=3;i++){
		hold_Mos[i] = buff[i];
	}
	for(int i=4;i<=7;i++){
		hold_Con[i] = buff[i];
	}
memcpy(&mosfetTemp, hold_Mos, sizeof(float));
memcpy(&controllerTemp, hold_Con, sizeof(float));
}

float Mpptx2::getMosfetTemp() const {
	return mosfetTemp;
}

float Mpptx2::getControllerTemp() const {
	return controllerTemp;
}

Mpptx3::Mpptx3(uint32_t can_id): // INCREMENT BY 3 FROM MPPTx0
	DataModule(can_id, 0, SIZE),
	aux12V(0),
	aux3V(0) // unsure if i need to do this, orionBMS doesnt but steering does
{}

void Mpptx3::ToByteArray(uint8_t* buff) const
{
uint8_t hold_12V[sizeof(float)];
uint8_t hold_3V[sizeof(float)];

memcpy(hold_12V, &aux12V, sizeof(float));
memcpy(hold_3V, &aux3V, sizeof(float));

	for (int i=0;i<=3;i++){
		buff[i] = hold_12V[i];
	}
	for (int i=4;i<=7;i++){
		buff[i] = hold_3V[i];
	}
}

void Mpptx3::FromByteArray(uint8_t* buff)
{
uint8_t hold_12V[sizeof(float)];
uint8_t hold_3V[sizeof(float)];

	for(int i=0;i<=3;i++){
		hold_12V[i] = buff[i];
	}
	for(int i=4;i<=7;i++){
		hold_3V[i] = buff[i];
	}
memcpy(&aux12V, hold_12V, sizeof(float));
memcpy(&aux3V, hold_3V, sizeof(float));
}

float Mpptx3::getAux12V() const {
	return aux12V;
}

float Mpptx3::getAux3V() const {
	return aux3V;
}

Mpptx4::Mpptx4(uint32_t can_id): // INCREMENT BY 4 FROM MPPTx0
	DataModule(can_id, 0, SIZE),
	maxOutputVoltage(0),
	maxInputCurrent(0) // unsure if i need to do this, orionBMS doesnt but steering does
{}

void Mpptx4::ToByteArray(uint8_t* buff) const
{
uint8_t hold_MOV[sizeof(float)];
uint8_t hold_MIC[sizeof(float)];

memcpy(hold_MOV, &maxOutputVoltage, sizeof(float));
memcpy(hold_MIC, &maxInputCurrent, sizeof(float));

	for (int i=0;i<=3;i++){
		buff[i] = hold_MOV[i];
	}
	for (int i=4;i<=7;i++){
		buff[i] = hold_MIC[i];
	}
}

void Mpptx4::FromByteArray(uint8_t* buff)
{
uint8_t hold_MOV[sizeof(float)];
uint8_t hold_MIC[sizeof(float)];

	for(int i=0;i<=3;i++){
		hold_MOV[i] = buff[i];
	}
	for(int i=4;i<=7;i++){
		hold_MIC[i] = buff[i];
	}
memcpy(&maxOutputVoltage, hold_MOV, sizeof(float));
memcpy(&maxInputCurrent, hold_MIC, sizeof(float));
}

float Mpptx4::getMaxOutputVoltage() const {
	return maxOutputVoltage;
}

float Mpptx4::getMaxInputCurrent() const {
	return maxInputCurrent;
}
}
