#pragma once

#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"
#include "../vendor/glm/gtc/type_ptr.hpp"


#include <iostream>
#include <vector>
#include <string>
#include <map>

#include <memory>



enum Direction
{
	DirNone,
	Forward,
	Right,
	Backwards,
	Left
};

static void AddDirectionToCoordinate(Direction direction, int& x, int& y)
{
	switch (direction)
	{
	case Direction::Forward: x += 0; y += -1; break;
	case Direction::Right: x += 1; y += 0; break;
	case Direction::Backwards: x += 0; y += 1; break;
	case Direction::Left: x += -1; y += 0; break;
	}
}







