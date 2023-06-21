#pragma once
#include "geometry.h"
#include "shape.h"
#include "engine.h"
class Shape;

namespace engine {

class Raytracer{
public:
	int width, height;
	std::vector<std::shared_ptr<Shape>> shapes;
	Raytracer(int width, int height):width(width), height(height)
	{

	}
    void Render(std::vector<Vec3f>& pixels);
};
}