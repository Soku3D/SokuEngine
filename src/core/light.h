#pragma once
#ifndef ENGINE_CORE_LIGHT_H
#define ENGINE_CORE_LIGHT_H
#include "engine.h"
#include "geometry.h"
namespace engine {
class Light {
  public:
    Vec3f pos;
    Light(const Vec3f pos) : pos(pos) {}
};
}  // namespace engine
#endif