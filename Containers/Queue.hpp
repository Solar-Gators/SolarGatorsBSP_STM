// File Name: Queue.hpp
// Description: This is a module that implements a Queue (FIFO)
// Author: John Carr
// Date Created: 10/27/2021
// Last Modified by:
// Date Last Modified:

//Header Guards
#ifndef SOLARGATORS_BSP_CONTAINERS_INC_Queue_H_
#define SOLARGATORS_BSP_CONTAINERS_INC_Queue_H_

//Include Files
#include <iterator>

//C Interface
#ifdef __cplusplus
extern "C" {
#endif
//C Public Constants
/*This is an example description for constants and variables. Delete this if it is unused here and copy and paste it to where it is needed. */
/**
 * @brief This is a brief description
 */

//C Public Variables

//C Public Function Prototypes
/*This is an example description for function prototypes. Delete this if it is unused here and copy and paste it to where it is needed. */
/**
 * @brief This is a brief description
 * @param Input_Param_Name - Description of input parameter
 * @ret Description of return value
 */


#ifdef __cplusplus
}
#endif //End C Interface

//C++ Interface

//Class Definitions
namespace SolarGators::Containers
{
  template<typename T, uint32_t Size>
  class Queue
  {
  public:
    Queue(bool allow_overwrite = false);
    bool Enqueue(T& new_data);
    T& Dequeue();
    T& Peak();
    bool IsEmpty();
    bool IsFull();
    static constexpr uint32_t MAX_SIZE = Size;
    const bool allow_overwrite_;
  private:
    T& arr_[Size];
    uint32_t front_;
    uint32_t rear_;
    uint32_t count_;
  };
}

  template<typename T, uint32_t Size>
  Queue<T, Size>::Queue(bool allow_overwrite):allow_overwrite_(allow_overwrite), front_(0), rear_(0), count(0)
  {}

  template<typename T, uint32_t Size>
  bool Queue<T, Size>::Enqueue(T& new_data)
  {
    if(!allow_overwrite_ && count_ >= MAX_SIZE)
    {
      return false;
    }
    else
    {
      arr_[rear_++] = new_data;
      if(rear >= MAX_SIZE)
        rear = 0;
      count_++;
    }
  }

  template<typename T, uint32_t Size>
  T& Queue<T, Size>::Dequeue()
  {
    if(count_ == 0)
    {
      return arr_[front_];
    }
    else
    {
      T& data= arr[front_++];
      if(front_ > MAX_SIZE)
        front_ = 0;
      return data;
    }
  }

  template<typename T, uint32_t Size>
  T& Queue<T, Size>::Peak()
  {
    return arr_[front_];
  }

#endif // SOLARGATORS_BSP_CONTAINERS_INC_Queue_H_
