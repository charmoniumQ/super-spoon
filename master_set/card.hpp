#ifndef CARD_H
#define CARD_H

#include <string>
#include <array>

class Card {
public:
  Card(const std::string& input);
  Card(uint8_t data);
  Card();
  friend Card operator+(const Card& card1, const Card& card2);
  friend bool operator==(const Card& card1, const Card& card2);
  friend bool operator!=(const Card& card1, const Card& card2);
  Card operator-() const;
  std::string str() const;
  std::array<uint8_t, 4> to_digits() const;
  void from_digits(std::array<uint8_t, 4> digits);
private:
  uint8_t data;
};

#endif
