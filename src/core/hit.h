#pragma once
#ifndef ENGINE_CORE_HIT_H
#define ENGINE_CORE_HIT_H
#include "engine.h"
#include "geometry.h"

namespace engine {

class Hit {
  public:
    float d;
    Vec3f point;
    Vec3f normal;
    std::shared_ptr<Shape> pShape;
    Vec2f uv;
    Hit(float d, const Vec3f& point, const Vec3f& normal)
        : d(d), point(point), normal(normal), pShape(nullptr)
    {
    }
};
}  // namespace engine
#endif