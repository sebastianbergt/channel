/**
 * @brief A template class for a channel that mimics Go-style channels.
 *
 * This class template represents a channel that can store elements of any type
 * T with a buffer size of N. The class provides methods to send and receive
 * elements in the channel, using a std::condition_variable and std::mutex to
 * control access to the buffer.
 */

#pragma once

#include <condition_variable>
#include <mutex>
#include <queue>
#include "static_queue.h"

namespace sbe {

template <typename T, size_t N> class Channel {
public:
  /**
   * @brief Constructs a channel with a buffer size of N.
   * @tparam T The type to be stored.
   * @tparam N how many instances of T can be stored before the queue is full.
   */
  Channel() : buffer_{}, mutex_{}, cv_{} {}

  /**
   * @brief Sends an element x on the channel.
   * @param x The element to be sent on the channel.
   */
  void send(T x) {
    std::unique_lock<std::mutex> lock(mutex_);
    cv_.wait(lock, [this] { return buffer_.size() < N; });
    buffer_.push(x);
    cv_.notify_one();
  }

  /**
   * @brief Receives an element from the channel.
   * @return The received element.
   */
  T recv() {
    std::unique_lock<std::mutex> lock(mutex_);
    cv_.wait(lock, [this] { return !buffer_.empty(); });
    T x = buffer_.front();
    buffer_.pop();
    cv_.notify_one();
    return x;
  }

private:
  ///< The buffer where the elements of the channel are stored.
  detail::StaticQueue<T, N> buffer_;
  ///< The mutex used to control access to the buffer.
  std::mutex mutex_;
  ///< The condition variable used to synchronize the send and receive
  ///< operations.
  std::condition_variable cv_;
};

} // namespace sbe