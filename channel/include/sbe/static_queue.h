/**
 * @brief A template class for a statically allocated queue.
 *
 * This class template represents a statically allocated queue that can store
 * elements of any type T with a buffer size of N. The class provides methods to
 * push, pop, and access elements in the queue, as well as check if the queue is
 * empty or full.
 */

#pragma once

#include <array>

namespace sbe {
namespace detail {

template <typename T, size_t N> class StaticQueue {
public:
  /**
   * @brief Constructs an empty queue of type T with a buffer size of N.
   * @tparam T The type to be stored.
   * @tparam N how many instances of T can be stored before the queue is full.
   */
  StaticQueue() : head_{}, tail_{}, size_{} {}

  /**
   * @brief Pushes an element x onto the back of the queue.
   * @attention Make sure the queue is not full.
   * @param x The element to be pushed onto the queue.
   */
  void push(const T &x) {
    data_[tail_] = x;
    tail_ = (tail_ + 1) % N;
    ++size_;
  }

  /**
   * @brief Returns the front element of the queue without removing it.
   * @return The front element of the queue.
   */
  T front() { return data_[head_]; }

  /**
   * @brief Removes the front element of the queue.
   */
  void pop() {
    head_ = (head_ + 1) % N;
    --size_;
  }

  /**
   * @brief Checks if the queue is empty.
   * @return True if the queue is empty, false otherwise.
   */
  bool empty() { return size_ == 0; }

  /**
   * @brief Checks if the queue is full.
   * @return True if the queue is full, false otherwise.
   */
  bool full() { return size_ == N; }

  /**
   * @brief Returns the number of elements currently in the queue.
   * @return The number of elements in the queue.
   */
  size_t size() { return size_; }

private:
  ///< The buffer where the elements of the queue are stored.
  std::array<T, N> data_;
  ///< The index of the front element of the queue.
  size_t head_;
  ///< The index of the next position to insert an element in the queue.
  size_t tail_;
  ///< The number of elements currently in the queue.
  size_t size_;
};

} // namespace detail
} // namespace sbe