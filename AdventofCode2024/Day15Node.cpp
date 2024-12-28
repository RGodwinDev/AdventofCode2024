#include "Day15Node.h"

Day15Node::Day15Node(char c) {
	if (c == '#') {
		this->empty = false;
		this->rock = true;
	}
	else if (c == 'O') {
		this->empty = false;
		this->rock = false;
	}
	else {
		this->empty = true;
		this->rock = false;
	}
}