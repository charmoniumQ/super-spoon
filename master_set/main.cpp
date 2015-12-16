#include <vector>
#include <iostream>
#include "card.hpp"
#include "thread_pool.hpp"
#include "miterator.hpp"

/*
g++ -std=c++11 -pthread -Wall -g -o main *.cpp
*/

void test1() {
  Card c1 ("0120");
  Card c2 ("1201");
  Card c3 = -(c1 + c2);
  Card c4 = c1 + c2 + c3;
  std::cout << c1.str() << " " << c2.str() << " " << c4.str() << " " << std::endl;
}

std::tuple<uint8_t, bool> worker_func(uint8_t i, uint8_t pid) {
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  std::cout << "opterating on " << (int)i << " from thread: " << (int)pid << std::endl;
  if (i == 13) {
	return std::make_tuple(i, true);
  } else {
	return std::make_tuple(0, false);
  }
}

void test2() {
  std::vector<uint8_t> input; input.reserve(100);
  for (int i = 0; i < 20; ++i) {
	input.push_back(i);
  }

  int val = 0;
  bool success = false;
  std::tie(val, success) = mrd<std::vector<uint8_t>::iterator, uint8_t, uint8_t>(worker_func, input.begin(), input.end(), 3);
  std::cout << "result: " << success << " with " << val << std::endl;
}

int main(int argc, char* argv[]) {
  test2();
  return 0;
}
