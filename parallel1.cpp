#include <iostream>
#include <future>
#include <thread>
#include <exception>
#include <chrono>

auto work = [](int a,char ch) {
	for (int i = 0; i < 5; i++) {
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		std::cout << ch;
	}
	return a;
};

auto func1 = [] () {
	return work(2, '.');
};

auto func2 = [] () {
	return work(2, '-');
};

int main()
{
	std::future<int> result1(std::async(func1));
	int result2 = func2();
	int result = result1.get() + result2;

	std::cout <<std::endl<< result;
	return 0;
}