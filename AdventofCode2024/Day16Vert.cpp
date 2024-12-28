#include "Day16Vert.h"

Day16Vert::Day16Vert(Day16Vert* pred, int i, int j) {
	this->pred = pred;
	this->pos = { i,j };
}