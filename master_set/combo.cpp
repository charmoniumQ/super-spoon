#include "combo.hpp"

Combinations::Combinations(uint8_t p_m, uint8_t q_m) : 
  q (q_m),
  p (p_m),
  data (q) {
  for (int i = 0; i < q; ++i) {
	data[i] = i;
  }
}

Combinations::Combinations(const Combinations& other) :
  q (other.p),
  p (other.q),
  data (other.data) { }

std::vector<int> Combinations::operator*() {
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
  for (int i = q - 1; i >= 0; --i) {
	if (data[i] >= p - q + i + 1) {
	  data[i] = 0;
	  if (i > 0) {
		data[i - 1]++;
	  } else {
		data[0] = p; // signal that I am done
	  }
	}
  }
  for (int i = 1; i < q; ++i) {
	if (data[i] == 0) {
	  data[i] = data[i - 1] + 1;
	}
  }
}

bool Combinations::has_next() const {
  return data[0] < p;
}
