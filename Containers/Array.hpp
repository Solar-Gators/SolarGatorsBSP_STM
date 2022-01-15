/*
 * Array.hpp
 *
 *  Created on: Nov 9, 2021
 *      Author: John Carr
 */

#ifndef SOLARGATORSBSP_CONTAINERS_ARRAY_HPP_
#define SOLARGATORSBSP_CONTAINERS_ARRAY_HPP_

#include <iterator> // For std::forward_iterator_tag
#include <cstddef>  // For std::ptrdiff_t

namespace SolarGators::Containers
{
  template<typename DATA_T, int SIZE>
  class Array
  {
  public:
    Array()
    {
      for(uint32_t i = 0; i < size; ++i)
        data_[i] = 0;
    }
    ~Array() {}
    DATA_T& operator[](uint32_t index)
    {
      return data_[index];
    }
    static constexpr uint32_t size_ = SIZE;
    struct Iterator
    {
      using iterator_category = std::forward_iterator_tag;
      using difference_type   = std::ptrdiff_t;
      using value_type        = DATA_T;
      using pointer           = DATA_T*;
      using reference         = DATA_T&;
      Iterator(pointer ptr) : ptr_(ptr) {}
      reference operator*() const { return *ptr_; }
      pointer operator->() { return ptr_; }

      // Prefix increment
      Iterator& operator++() { ptr_++; return *this; }

      // Postfix increment
      Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

      friend bool operator== (const Iterator& a, const Iterator& b) { return a.ptr_ == b.ptr_; };
      friend bool operator!= (const Iterator& a, const Iterator& b) { return a.ptr_ != b.ptr_; };
    private:
      pointer ptr_;
    };
    Iterator begin() { return Iterator(&data_[0]); }
    Iterator end()   { return Iterator(&data_[SIZE]); }
  private:
    DATA_T data_[SIZE];
  };
}


#endif /* SOLARGATORSBSP_CONTAINERS_ARRAY_HPP_ */
