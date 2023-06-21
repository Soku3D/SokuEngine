#pragma once
#include "engine.h"
#include "geometry.h"
#include "texture.h"
namespace engine{

class Shape{
    Vec3f amb;
    Vec3f dif;
    Vec3f spec;
    
	float reflection, transparency;
};
}
