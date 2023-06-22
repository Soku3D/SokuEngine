#pragma once

#ifndef ENGINE_CORE_SHAPE_H
#define ENGINE_CORE_SHAPE_H
#include "engine.h"
#include "geometry.h"
#include "hit.h"
#include "texture.h"
namespace engine {
class Shape {
  public:
    Vec3f amb;
    Vec3f dif;
    Vec3f spec;
    float ks;
    float alpha;
    float reflection, transparency;
    std::shared_ptr<Texture> ambTexture;
    std::shared_ptr<Texture> difTexture;

    Shape(const Vec3f& color = Vec3f(0.0f), float reflection = 0.0f,
          float transparency = 0.0f)
        : amb(color),
          dif(color),
          spec(color),
          reflection(reflection),
          transparency(transparency),
          ks(0.0f),
          alpha(0.0f) {}
    virtual Hit CheckRayCollision(const Ray& ray) = 0;
};

class Sphere : public Shape {
  public:
    Vec3f center;
    float radius;
    Sphere(const Vec3f& center, float r, const Vec3f& color = Vec3f(0.0f))
        : center(center), radius(r), Shape(color) {}

    // ||O+td-C|| = r*r
    virtual Hit CheckRayCollision(const Ray& ray) override {
        Hit hit{-1.0f, Vec3f(0.0f), Vec3f(0.0f)};
        Vec3f co = ray.o - center;
        float b = dot(ray.d, co);
        float c = dot(co, co) - radius * radius;
        float nabla = b * b - c;
        if (nabla >= 0.0f) {
            float d1 = -b + std::sqrt(nabla);
            float d2 = -b - std::sqrt(nabla);

            hit.d = std::min(d1, d2);
            if (GetLen(co) < radius) hit.d = std::max(d1, d2);
            hit.point = ray(hit.d);
            Vec3f cp = hit.point - center;
            hit.normal = normalize(cp);
        }
        return hit;
    }
};

}  // namespace engine
#endif