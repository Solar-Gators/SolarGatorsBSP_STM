/*
 * MPPT.hpp
 *
 *  Created on: Apr 17, 2023
 *      Author: Jack W
 */

#ifndef SOLARGATORSBSP_STM_DATAMODULES_INC_MPPT_HPP_
#define SOLARGATORSBSP_STM_DATAMODULES_INC_MPPT_HPP_

#include <DataModule.hpp>
#include <cstdint>

namespace SolarGators::DataModules
{
	class Mpptx0 final: public DataModule {
	public:
		Mpptx0(uint32_t can_id);
		~Mpptx0() {};

		float getInputVoltage() const;
		float getInputCurrent() const;

		void ToByteArray(uint8_t* buff) const;
		void FromByteArray(uint8_t* buff);
	protected:
		float inputVoltage;
		float inputCurrent;
	};

	class Mpptx1 final: public DataModule {
	public:
		Mpptx1(uint32_t can_id);
		~Mpptx1() {};

		float getOutputVoltage() const;
		float getOutputCurrent() const;

		void ToByteArray(uint8_t* buff) const;
		void FromByteArray(uint8_t* buff);
	protected:
		float outputVoltage;
		float outputCurrent;
	};

	class Mpptx2 final: public DataModule {
		public:
			Mpptx2(uint32_t can_id);
			~Mpptx2() {};

			float getMosfetTemp() const;
			float getControllerTemp() const;

			void ToByteArray(uint8_t* buff) const;
			void FromByteArray(uint8_t* buff);
		protected:
			float mosfetTemp;
			float controllerTemp;
	};

	class Mpptx3 final: public DataModule {
		public:
			Mpptx3(uint32_t can_id);
			~Mpptx3() {};

			float getAux12V() const;
			float getAux3V() const;

			void ToByteArray(uint8_t* buff) const;
			void FromByteArray(uint8_t* buff);
		protected:
			float aux12V;
			float aux3V;
	};

	class Mpptx4 final: public DataModule {
		public:
			Mpptx4(uint32_t can_id);
			~Mpptx4() {};

			float getMaxOutputVoltage() const;
			float getMaxInputCurrent() const;

			void ToByteArray(uint8_t* buff) const;
			void FromByteArray(uint8_t* buff);
		protected:
			float maxOutputVoltage;
			float maxInputCurrent;
		};
}


#endif /* SOLARGATORSBSP_STM_DATAMODULES_INC_MPPT_HPP_ */
