#include <tuple>
#include <vector>
#include <bitset>
#include <iostream>
#include "card.hpp"
#include "thread_pool.hpp"
#include "combo.hpp"

/*
g++ -std=c++11 -pthread -Wall -Wpedantic -Wextra -Og -pg -g -o main *.cpp
g++ -std=c++11 -pthread -w -Ofast -o main *.cpp
*/

void test1() {
  Card c1 ("0120");
  Card c2 ("1201");
  Card c3 = -(c1 + c2);
  Card c4 = c1 + c2 + c3;
  Card zero ("0000");
  std::cout << c1.str() << " "
			<< c2.str() << " "
			<< c3.str() << " "
			<< c4.str() << " "
			<< (c1 != zero) << (c1 == zero) << (c4 == zero) << std::endl;
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
  std::tie(val, success) = mrd<std::vector<uint8_t>::const_iterator, uint8_t, uint8_t>(worker_func, input.cbegin(), input.cend(), 3);
  std::cout << "result: " << success << " with " << val << std::endl;
}

void print_vec(const std::vector<uint8_t>& data) {
  for (std::vector<uint8_t>::const_iterator it = data.cbegin(); it != data.cend(); ++it) {
	int j = *it;
	std::cout << j << " ";
  }
  std::cout << std::endl;
}

void test3() {
  Combinations c (5, 3);
  for (; c != c.end(); ++c) {
	print_vec(*c);
  }
}

bool has_set(const std::bitset<81>& table_tr, std::vector<Card> table_vec) {
  for (uint8_t i = 0; i < table_vec.size(); ++i) {
	for (uint8_t j = i + 1; j < table_vec.size(); ++j) {
	  if (table_tr[complement(table_vec[i], table_vec[j])]) {
		return true;
	  }
	}
  }
  return false;
}

std::tuple<std::vector<Card>, bool> worker_func2(uint8_t n, uint8_t start, uint8_t pid) {
  Combinations combo (81, n - 2);
  const Card first[4] = {0, 1, 4, 5};
  // first[0] == Card("0000");
  // first[1] == Card("0001");
  // first[2] == Card("0011");
  // first[3] == Card("0012");

  std::vector<Card> table_vec (n);
  std::bitset<81> table_tr (0L);
  while (combo.has_next()) {
	auto it = (*combo).cbegin();
	for (uint8_t i = 0; it != (*combo).cend(); ++i, ++it) {
	  table_tr.set(Card(*it));
	  table_vec[i] = Card(*it);
	}

	if (!table_tr[Card(start)]) {
	  table_vec[n - 2] = Card(start);
	  table_tr.set(Card(start));
	  
	  for (uint8_t i = 0; i < 4; ++i) {
		if (!table_tr[first[i]]) {
		  table_tr.set(first[i]);
		  table_vec[n - 1] = first[i];
		  
		  if (! has_set(table_tr, table_vec)) {
			return std::make_tuple(table_vec, true);
		  }
		  
		  table_tr.reset(first[i]);
		  table_vec[n - 1] = 0;
		}
	  }
	}
	combo.next();
  }

  std::vector<Card> c;
  return std::make_tuple(c, false);
}

int main(int argc, char* argv[]) {
  test3();
  return 0;
}
