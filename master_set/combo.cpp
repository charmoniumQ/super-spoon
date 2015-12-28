#include "combo.hpp"

Combinations::Combinations(uint8_t p_m, uint8_t q_m) : 
  p (p_m),
  q (q_m),
  data (q) {
  for (uint8_t i = 0; i < q; ++i) {
	data[i] = i;
  }
}

Combinations::Combinations(const Combinations& other) :
  p (other.q),
  q (other.p),
  data (other.data) { }

const std::vector<uint8_t>& Combinations::operator*() const {
  return data;
}

const Combinations& Combinations::operator++() {
  next();
  return *this;
}

Combinations Combinations::operator++(int) {
  Combinations output (*this);
  next();
  return output;
}

bool operator==(const Combinations& c1, const Combinations& c2) {
  if (!c1.has_next() && !c2.has_next()) {
	// if they are both done,
	// nothign else matters
	return true;
  }
  return c1.data == c2.data;
}

bool operator!=(const Combinations& c1, const Combinations& c2) {
  return ! (c1 == c2);
}

const Combinations Combinations::end() const {
  Combinations output (*this);
  output.data[0] = p;
  return output;
}

void Combinations::next() {
  data[q - 1]++;
  for (uint8_t i = q; i > 0; --i) {
	if (data[i-1] >= p - q + i) {
	  data[i-1] = 0;
	  if (i > 1) {
		data[i - 2]++;
	  } else {
		data[0] = p; // signal that I am done
	  }
	}
  }
  for (uint8_t i = 1; i < q; ++i) {
	if (data[i] == 0) {
	  data[i] = data[i - 1] + 1;
	}
  }
}

bool Combinations::has_next() const {
  return data[0] < p;
}
