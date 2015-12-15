#include <iostream>
#include <card.hpp>

void test1() {
  Card c1 ("0120");
  Card c2 ("1201");
  Card c3 = -(c1 + c2);
  Card c4 = c1 + c2 + c3;
  std::cout << c1.str() << " " << c2.str() << " " << c4.str() << " " << std::endl;
}

int main(int argc, char* argv[]) {
  test1();
}
