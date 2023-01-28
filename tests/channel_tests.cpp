#include <catch2/catch_test_macros.hpp>
#include <thread>

#include <sbe/channel.h>

SCENARIO("Sunny day: Test send and recv on channel with ints") {
  GIVEN("A channel of 5 integers") {
    sbe::Channel<int, 5> c;
    WHEN("sending a value") {
      std::thread t1([&] { c.send(42); });
      THEN("this value is received") {
        std::thread t2([&] {
          int x = c.recv();
          REQUIRE(x == 42);
        });
        t1.join();
        t2.join();
      }
    }
  }
}

SCENARIO("Test send and recv on channel with strings", "[channel]") {
  GIVEN("A channel of 5 strings") {
    sbe::Channel<std::string, 5> c;
    WHEN("sending a message") {
      std::thread t1([&] { c.send("hello"); });
      THEN("this message is received") {
        std::thread t2([&] {
          std::string s = c.recv();
          REQUIRE(s == "hello");
        });
        t1.join();
        t2.join();
      }
    }
  }
}

SCENARIO("Test send and recv on full channel", "[channel]") {
  GIVEN("A channel of 1 int") {
    sbe::Channel<int, 1> c;
    WHEN("filling up the channel, the second value waits to be added") {
      c.send(1);
      std::thread t1([&] { c.send(2); });
      THEN("receiving one value after the other") {
        std::thread t2([&] {
          int x = c.recv();
          REQUIRE(x == 1);
          x = c.recv();
          REQUIRE(x == 2);
        });
        t1.join();
        t2.join();
      }
    }
  }
}