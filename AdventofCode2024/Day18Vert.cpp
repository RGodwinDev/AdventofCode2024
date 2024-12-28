#include "Day18Vert.h"

Day18Vert::Day18Vert(int value) {
	this->value = value;
	this->pred = nullptr;
	this->distance = INT_MAX;
}