#include <string>

class Card {
public:
  Card operator+(const Card& card);
  Card operator-();
  std::string str();
  Card(const std::string input);
  Card();
private:
  uint16_t data;
};
