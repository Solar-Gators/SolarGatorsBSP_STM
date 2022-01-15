/*
 * DataModule.h
 *
 *  Created on: Oct 29, 2021
 *      Author: John Carr
 */

#ifndef SOLARGATORSBSP_DATAMODULES_INC_DATAMODULE_HPP_
#define SOLARGATORSBSP_DATAMODULES_INC_DATAMODULE_HPP_

#include <cstdint>
#include <cmsis_os.h>

namespace SolarGators {
namespace DataModules {

class DataModule {
public:
  DataModule(uint32_t id, uint32_t size, bool is_ext_id = false):
    id_(id), size_(size), is_ext_id_(false)
  {
    mutex_id_ = osMutexNew(&mutex_attributes_);
  };
  virtual ~DataModule() {};
  virtual void ToByteArray(uint8_t* buff) const = 0;
  virtual void FromByteArray(uint8_t* buff) = 0;
  const uint32_t id_;
  const uint32_t size_;
  const bool is_ext_id_;
  osMutexId_t mutex_id_;
  StaticSemaphore_t mutex_control_block_;
  const osMutexAttr_t mutex_attributes_ = {
    .name = "DMM",
    .attr_bits = osMutexRecursive,
    .cb_mem = &mutex_control_block_,
    .cb_size = sizeof(mutex_control_block_),
  };
};

} /* namespace DataModules */
} /* namespace SolarGators */

#endif /* SOLARGATORSBSP_DATAMODULES_INC_DATAMODULE_HPP_ */
