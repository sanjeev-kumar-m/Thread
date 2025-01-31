#include <iostream>
#include <vector>
#include <thread>
#include <Thread/Thread.hpp>

class NaturalNumberGenerator : public Thread::Thread {
  protected:
    void thread_main() override {
      for(int i =0; i < 10; ++i) {
        std::cout << "i : " << i << std::endl;
      }
    }

    void stop() override {
      return;
    }
};

int main() {
  NaturalNumberGenerator nm;
  if (nm.run() != Thread::ThreadStatus::Ok) {
    std::cout << "Failed to create thread" << std::endl;
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}