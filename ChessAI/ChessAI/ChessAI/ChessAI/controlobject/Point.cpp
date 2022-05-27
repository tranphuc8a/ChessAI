#include "../hdr/Point.h"

Point::Point() {
	r = c = 0;
}

Point::Point(int r, int c) {
	this->r = r;
	this->c = c;
}

void Point::set(int x, int y) {
	this->r = x;
	this->c = y;
}


