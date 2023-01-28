## What is Channel?

The template class Channel that can store elements of any type
T with a buffer size of N. The class provides methods to send and receive
elements in the channel, using a std::condition_variable and std::mutex to
control access to the buffer.

The data is stored in a statically allocated queue, which utilizes std::array.

It is written in C++14.

## How to use it

```cpp
#include <iostream>
#include <thread>
#include <sbe/channel.h>

template<typename ChannelType>
void producer(ChannelType &ch) {
    for (int i = 0; i < 10; ++i) {
        ch.send(i);
        std::cerr << "Sent: " << i << std::endl;
    }
}

template<typename ChannelType>
void consumer(ChannelType &ch) {
    for (int i = 0; i < 10; ++i) {
        std::cerr << "Received: " << ch.recv() << std::endl;
    }
}

int main() {
    using IntChannel = sbe::Channel<int, 10>;
    IntChannel ch;

    std::thread t1(producer<IntChannel>, std::ref(ch));
    std::thread t2(consumer<IntChannel>, std::ref(ch));

    t1.join();
    t2.join();

    return 0;
}
```

## More
* Issues and bugs can be raised on the [Issue tracker on GitHub](https://github.com/sebastianbergt/channel/issues)
* Unit tests utilize the excellent [Catch2 library](https://github.com/catchorg/Catch2)