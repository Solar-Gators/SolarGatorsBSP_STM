/*
 * CAN.cpp
 *
 *  Created on: Oct 29, 2021
 *      Author: John Carr
 */

#include <CAN.hpp>

namespace SolarGators {
namespace Drivers {

CANDriver::CANDriver(CAN_HandleTypeDef& hcan, uint32_t rx_fifo_num_):hcan_(hcan),rx_fifo_num_(rx_fifo_num_)
{
  can_rx_event_ = osEventFlagsNew(NULL);
  if (can_rx_event_ == NULL)
  {
      Error_Handler();
  }

  rx_task_handle_ = osThreadNew((osThreadFunc_t)&CANDriver::HandleReceive, this, &rx_task_attributes_);
  if (rx_task_handle_ == NULL)
  {
      Error_Handler();
  }
}

CANDriver::~CANDriver()
{ }

void CANDriver::HandleReceive()
{
  while(1)
  {
    osEventFlagsWait(can_rx_event_, 0x1, osFlagsWaitAny, osWaitForever);
    CAN_RxHeaderTypeDef pHeader;
    uint8_t aData[MAX_DATA_SIZE];

    while(HAL_CAN_GetRxFifoFillLevel(&hcan_, rx_fifo_num_))
    {
      HAL_CAN_GetRxMessage(&hcan_, rx_fifo_num_, &pHeader, aData);
      DataModules::DataModule* rx_module = modules_.Find(pHeader.IDE == CAN_ID_STD ? pHeader.StdId : pHeader.ExtId);
      if(rx_module != nullptr)
      {
        osMutexAcquire(rx_module->mutex_id_, osWaitForever);
        rx_module->FromByteArray(aData);
        osMutexRelease(rx_module->mutex_id_);
      }
    }
  }
}

void CANDriver::Send(SolarGators::DataModules::DataModule* data)
{
  //Spinlock until a tx mailbox is empty
  while(!HAL_CAN_GetTxMailboxesFreeLevel(&hcan_));

  //Initialize Header
  uint32_t pTxMailbox;
  CAN_TxHeaderTypeDef pHeader;
  pHeader.RTR = CAN_RTR_DATA;
  pHeader.DLC = data->size_;
  if(data->is_ext_id_)
  {
    pHeader.ExtId = data->id_;
    pHeader.IDE = CAN_ID_EXT;
  }
  else
  {
    pHeader.StdId = data->id_;
    pHeader.IDE = CAN_ID_STD;
  }
  //Put CAN message in tx mailbox
  uint8_t aData[MAX_DATA_SIZE];
  osMutexAcquire(data->mutex_id_, osWaitForever);
  data->ToByteArray(aData);
  osMutexRelease(data->mutex_id_);
  HAL_CAN_AddTxMessage(&hcan_, &pHeader, aData, &pTxMailbox);
}

bool CANDriver::AddRxModule(DataModules::DataModule* module)
{
  return modules_.Insert(module->id_, module);
}

bool CANDriver::RemoveRxModule(uint32_t module_id)
{
  // TODO: Implement (Remove needs to be added to tree container)
  return false;
}

void CANDriver::SetRxFlag()
{
  osEventFlagsSet(can_rx_event_, 0x1);
}

} /* namespace Drivers */
} /* namespace SolarGators */
