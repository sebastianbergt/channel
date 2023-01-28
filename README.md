# Channel

The template class Channel that can store elements of any type
T with a buffer size of N. The class provides methods to send and receive
elements in the channel, using a std::condition_variable and std::mutex to
control access to the buffer.

The data is stored in a statically allocated queue, which utilizes std::array.

Written in C++14.

```cpp
# example/src/main.cpp
```