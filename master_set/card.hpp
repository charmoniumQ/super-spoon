#ifndef CARD_H
#define CARD_H

#include <string>
#include <array>
#include <cstdint>

class Card {
public:
  Card(const std::string& input);
  Card(uint8_t data);
  Card();
  const Card& operator++();
  Card operator++(int);
  friend Card operator+(Card card1, Card card2);
  friend bool operator==(Card card1, Card card2);
  friend bool operator!=(Card card1, Card card2);
  Card operator-() const;
  friend Card complement(Card card1, Card card2);
  std::string str() const;
  std::array<uint8_t, 4> to_digits() const;
  void from_digits(std::array<uint8_t, 4> digits);
  operator int() const;
private:
  uint8_t data;
};

class Deck {
public:
  Deck(Card card_m);
  Deck();
  const Deck& operator++();
  Deck operator++(int);
  friend bool operator==(Deck c1, Deck c2);
  friend bool operator!=(Deck c1, Deck c2);
  const Deck end() const;
private:
  Card card;
};

#endif
