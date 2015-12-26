#ifndef COMBO_H
#define COMBO_H

#include <cstdint>
#include <vector>

class Combinations {
public:
  Combinations(uint8_t p, uint8_t q);
  Combinations(const Combinations& other);
  std::vector<int> operator*();
  const Combinations& operator++();
  Combinations operator++(int);
  friend bool operator==(const Combinations& c1, const Combinations& c2);
  friend bool operator!=(const Combinations& c1, const Combinations& c2);
  const Combinations end() const;
  bool has_next() const;
  void next();
private:
  uint8_t q, p;
  std::vector<int> data;
};

#endif
