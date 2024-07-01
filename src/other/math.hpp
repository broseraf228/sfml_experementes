#pragma once

struct Vect2i {
	Vect2i();
	Vect2i(int scallar);
	Vect2i(int x, int y);

	int x{ 0 }, y{ 0 };

	Vect2i operator + (const Vect2i&);
	Vect2i operator - (const Vect2i&);
	Vect2i operator * (float scallar);
};