#include <card.hpp>

Card Card::operator+(const Card& card) {
  Card output;
  uint16_t tmp = this->data + card.data;
  uint16_t lut[] = {0, 1, 2, 0, 1};
  output.data =
	lut[tmp >> 0 & 7] << 0 |
	lut[tmp >> 3 & 7] << 3 |
	lut[tmp >> 6 & 7] << 6 |
	lut[tmp >> 9 & 7] << 9 ;
  return output;
}

Card Card::operator-() {
  uint16_t lut[] = {0, 2, 1};
  Card output;
  output.data =
	lut[data >> 0 & 3] << 0 |
	lut[data >> 3 & 3] << 3 |
	lut[data >> 6 & 3] << 6 |
	lut[data >> 9 & 3] << 9 ;  
  return output;
}

Card::Card(const std::string input) {
  data =
	(input[0] - '0') << 9 |
	(input[1] - '0') << 6 |
	(input[2] - '0') << 3 |
	(input[3] - '0') << 0 ;
}

Card::Card() { }

std::string Card::str() {
#pragma GCC diagnostic ignored "-Wnarrowing"
  char output[5] = {
	(data >> 9 & 3) + '0',
	(data >> 6 & 3) + '0',
	(data >> 3 & 3) + '0',
	(data >> 0 & 3) + '0',
	'\0'
  };
#pragma GCC diagnostic pop
  std::string output2 (output);
  return output2;
}
