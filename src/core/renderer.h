#pragma once

#ifndef ENGINE_CORE_RENDERER_H
#define ENGINE_CORE_RENDERER_H
#include "engine.h"
#include "geometry.h"
#include "shape.h"
#include "light.h"
#include "hit.h"
namespace engine {

class Raytracer {
  public:
    int width, height;
    float invW, invH;
    float aspect;
    std::vector<std::shared_ptr<Shape>> shapes;
    Vec3f eyePos;
    Light light;
    Raytracer(int width, int height); 
    Hit FindClosestShape(const Ray& ray);
    Vec3f traceRay(const Ray& ray, int recursiveLevel);
    Vec3f traceRay2x2(const Vec3f& currPos, float currD, int recursiveLevel);
    void Render(std::vector<Vec3f>& pixels);
    Vec3f TransformScreenToWorld(int x, int y);
};
}  // namespace engine

#endif