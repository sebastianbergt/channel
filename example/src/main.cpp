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