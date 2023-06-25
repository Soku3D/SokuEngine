#pragma once

#ifndef ENGINE_CORE_RENDERER_H
#define ENGINE_CORE_RENDERER_H
#include "engine.h"
#include "geometry.h"
#include "hit.h"
#include "light.h"
#include "shape.h"
namespace engine {

class Raytracer {
  public:
    int width, height;
    float invW, invH;
    float aspect;
    Raytracer(int width, int height);

  public:
    std::vector<std::shared_ptr<Shape>> shapes;
    Vec3f eyePos;
    Light light;

  public:
    Hit FindClosestShape(const Ray& ray);
    bool IsShadow(const Ray& ray);
    Vec3f traceRay(const Ray& ray, int recursiveLevel);
    Vec3f traceRay2x2(const Vec3f& currPos, float currD, int recursiveLevel);
    void Render(std::vector<Vec3f>& pixels);
    Vec3f TransformScreenToWorld(int x, int y);
};
class Rasterization {
  public:
    int width, height;
    float aspect;
    Rasterization(const int& width, const int& height);
   
    Vec3f vertecies[3];
  public:
    float CCW(const Vec2f& v0, const Vec2f& v1, const Vec2f& point);
    Vec2f ProjectWorldToScreen(Vec3f vertex); 
    void Render(std::vector<Vec3f>& pixels);
     
};
}  // namespace engine

#endif