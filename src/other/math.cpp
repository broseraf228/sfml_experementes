#include "math.hpp"

Vect2i::Vect2i() {
	x = 0; y = 0;
}
Vect2i::Vect2i(int scallar) {
	x = scallar; y = scallar;
}
Vect2i::Vect2i(int x, int y) {
	this->x = x; this->y = y;
}

Vect2i Vect2i::operator+(const Vect2i& second) {
	return Vect2i(x + second.x, y + second.y);
}
Vect2i Vect2i::operator-(const Vect2i& second) {
	return Vect2i(x - second.x, y - second.y);
}
Vect2i Vect2i::operator*(float scallar) {
	return Vect2i(x * scallar, y * scallar);
}