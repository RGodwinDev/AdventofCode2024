#include "Day16Vert.h"

Day16Vert::Day16Vert(char c) {
	this->rock = c == '#';
	this->end = c == 'E';
}


bool Day16Vert::isRock() {
	return this->rock;
}
bool Day16Vert::isEnd() {
	return this->end;
}