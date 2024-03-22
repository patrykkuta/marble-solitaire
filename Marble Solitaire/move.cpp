#include "move.h"
#include <utility>

Move::Move(std::pair<short, short> origin, std::pair<short, short> destination) : origin(origin), destination(destination) {}
std::pair<short, short> Move::getOrigin() {
	return origin;
}

std::pair<short, short> Move::getDestination() {
	return destination;
}