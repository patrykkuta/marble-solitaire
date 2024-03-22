#pragma once
#include <utility>
class Move {
private:
	std::pair<short, short> origin;
	std::pair<short, short> destination;
public:
	Move(std::pair<short, short> origin, std::pair<short, short> destination);
	std::pair<short, short> getOrigin();
	std::pair<short, short> getDestination();
};

