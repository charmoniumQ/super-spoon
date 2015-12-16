#include "card.hpp"

int8_t pow(int8_t base, uint8_t exp) {
  int8_t result = 1;
  while (exp > 0) {
	result = result * base;
	exp--;
  }
  return result;
}

Card::Card(const std::string& input) {
  data = 
	(input[0] - '0') * 27 +
	(input[1] - '0') * 9  +
	(input[2] - '0') * 3  +
	(input[3] - '0') * 1  ;
}

Card::Card(uint8_t data_m) : data(data_m) { }

Card::Card() : Card(0) {}

Card operator+(const Card& card1, const Card& card2) {
  std::array<uint8_t, 4> digits1 = card1.to_digits(), digits2 = card2.to_digits(), sum;
  for (uint8_t i = 0; i < 4; ++i) {
	sum[i] = (digits1[i] + digits2[i]) % 3;
  }
  Card output;
  output.from_digits(sum);
  return output;
}

bool operator==(const Card& card1, const Card& card2) {
  return card1.data == card2.data;
}

bool operator!=(const Card& card1, const Card& card2) {
  return card1.data != card2.data;
}

Card Card::operator-() const {
  std::array<uint8_t, 4> digits = to_digits(), sum;
  for (uint8_t i = 0; i < 4; ++i) {
	sum[i] = (3 - digits[i]) % 3;
  }
  Card output;
  output.from_digits(sum);
  return output;
}

std::string Card::str() const {
#pragma GCC diagnostic ignored "-Wnarrowing"
  std::array<uint8_t, 4> digits = to_digits();  
  char output[5] = {
	(digits[0]) + '0',
	(digits[1]) + '0',
	(digits[2]) + '0',
	(digits[3]) + '0',
	'\0'
  };
#pragma GCC diagnostic pop
  std::string output2 (output);
  return output2;
}

std::array<uint8_t, 4> Card::to_digits() const {
  std::array<uint8_t, 4> output;
  uint8_t tdata (data);
  for (uint8_t i = 0; i < 4; ++i) {
	output[i] = tdata / pow(3, 3 - i);
	tdata %= pow(3, 3 - i);
  }
  return output;
}

void Card::from_digits(std::array<uint8_t, 4> digits) {
  data = 0;
  for (uint8_t i = 0; i < 4; ++i) {
	data += digits[i] * pow(3, 3 - i);
  }
}
