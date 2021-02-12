#include <iostream>
#include <memory>
#include <thread>
#include <mutex>

std::mutex my_mutex;
auto foo = [] (int i) {
  my_mutex.lock();
  std::cout << "Calling by Thread: " << i << "\n";
  my_mutex.unlock();
};

std::mutex m_mutex2;
auto hello = [] (std::string s) {
  std::lock_guard<std::mutex> g(m_mutex2);
  std::cout << "Hello from: " << s << "\n";
};

int main() {
  std::thread t1(foo, 1);
  std::thread t2(foo, 2);
  std::thread t3(foo, 3);
  std::thread t4(foo, 4);

  t1.join();
  t2.join();
  t3.join();
  t4.join();
  // calling in this way leads to sharing of function with different threads
  // at the same time as a result of which we can fall in race conditions
  // so to avoid race conditions we can lock the function while it is in use
  // with some thread X (say). we can put a lock on thread using mutex

  std::thread t5(hello, std::string("thread 5"));
  std::thread t6(hello, std::string("thread 6"));
  std::thread t7(hello, std::string("thread 7"));
  std::thread t8(hello, std::string("thread 8"));
  std::thread t9(hello, std::string("thread 9"));

  t5.join();
  t6.join();
  t7.join();
  t8.join();
  t9.join();
  return 0;
}
