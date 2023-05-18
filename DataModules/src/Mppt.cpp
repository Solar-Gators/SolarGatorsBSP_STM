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

union float2byte
{
	float f;
	char s[4];
};

float2byte f2b;

Mpptx0::Mpptx0(uint32_t can_id):
		DataModule(can_id, 0, SIZE),
		inputVoltage(0),
		inputCurrent(0) // unsure if i need to do this, orionBMS doesnt but steering does
		{}

void Mpptx0::ToByteArray(uint8_t* buff) const
{
	f2b.f = inputVoltage;
	for (int i=0;i<=3;i++){
		buff[i] = f2b.s[i];
	}
	f2b.f = inputCurrent;
	for (int i=4;i<=7;i++){
		buff[i] = f2b.s[i-4];
	}
}

void Mpptx0::FromByteArray(uint8_t* buff)
{
	for(int i=0;i<=3;i++){
		f2b.s[i] = buff[i];
	}
	inputVoltage = f2b.f;
	for(int i=4;i<=7;i++){
		f2b.s[i-4] = buff[i];
	}
	inputCurrent = f2b.f;
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
	f2b.f = outputVoltage;

	for (int i=0;i<=3;i++){
		buff[i] = f2b.s[i];
	}

	f2b.f = outputCurrent;

	for (int i=4;i<=7;i++){
		buff[i] = f2b.s[i-4];
	}
}

void Mpptx1::FromByteArray(uint8_t* buff)
{
	for(int i=0;i<=3;i++){
		f2b.s[i] = buff[i];
	}
	outputVoltage = f2b.f;

	for(int i=4;i<=7;i++){
		f2b.s[i-4] = buff[i];
	}
	outputCurrent = f2b.f;
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
	f2b.f = mosfetTemp;
	for (int i=0;i<=3;i++){
		buff[i] = f2b.s[i];
	}
	f2b.f = controllerTemp;
	for (int i=4;i<=7;i++){
		buff[i] = f2b.s[i-4];
	}
}

void Mpptx2::FromByteArray(uint8_t* buff)
{
	for(int i=0;i<=3;i++){
		f2b.s[i] = buff[i];
	}
	mosfetTemp = f2b.f;
	for(int i=4;i<=7;i++){
		f2b.s[i-4] = buff[i];
	}
	controllerTemp = f2b.f;
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
	f2b.f = aux12V;
	for (int i=0;i<=3;i++){
		buff[i] = f2b.s[i];
	}
	f2b.f = aux3V;
	for (int i=4;i<=7;i++){
		buff[i] = f2b.s[i-4];
	}
}

void Mpptx3::FromByteArray(uint8_t* buff)
{
	for(int i=0;i<=3;i++){
		f2b.s[i] = buff[i];
	}
	aux12V = f2b.f;
	for(int i=4;i<=7;i++){
		f2b.s[i-4] = buff[i];
	}
	aux3V = f2b.f;
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
	maxInputCurrent(0)
{}

void Mpptx4::ToByteArray(uint8_t* buff) const
{
	//need to be cautious of data types when using a union like this
	union{
		uint8_t y[4];
		float z;
	} data;

	data.z = maxOutputVoltage;
	buff[3] = data.y[3];
	buff[2] = data.y[2];
	buff[1] = data.y[1];
	buff[0] = data.y[0];

	data.z = maxInputCurrent;
	buff[7] = data.y[3];
	buff[6] = data.y[2];
	buff[5] = data.y[1];
	buff[4] = data.y[0];
}

void Mpptx4::FromByteArray(uint8_t* buff)
{
	//the below is an alernate way of type punning that i think is more safe cuz declared datatypes...
	//but i like the actual way better it looks more efficient
	/*
	unsigned long int maxVolt = (unsigned long int)buff[3]<<24|(unsigned long int)buff[2]<<16|(unsigned long int)buff[1]<<8|(unsigned long int)buff[0];
	unsigned long int maxCur = (unsigned long int)buff[7]<<24|(unsigned long int)buff[6]<<16|(unsigned long int)buff[5]<<8|(unsigned long int)buff[4];
	union
	{
		long y;
		float z;
	}data;
	data.y = maxCur;
	maxInputCurrent = data.z;
	data.y = maxVolt;
	maxOutputVoltage = data.z;
	*/
	for(int i=0;i<=3;i++){
		f2b.s[i] = buff[i];
	}
	maxOutputVoltage = f2b.f;
	for(int i=4;i<=7;i++){
		f2b.s[i-4] = buff[i];
	}
	maxInputCurrent = f2b.f;
}

float Mpptx4::getMaxOutputVoltage() const {
	//return float values
	return maxOutputVoltage;
}

float Mpptx4::getMaxInputCurrent() const {
	return maxInputCurrent;
}
}
