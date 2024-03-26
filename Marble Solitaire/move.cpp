#include "move.h"
#include <utility>

Move::Move(std::pair<short, short> origin, std::pair<short, short> destination) {
	this->origin.first = origin.first;
	this->origin.second = origin.second;
	this->destination.first = destination.first;
	this->destination.second = destination.second;
}
std::pair<short, short>& Move::getOrigin() {
	return origin;
}

std::pair<short, short>& Move::getDestination() {
	return destination;
}