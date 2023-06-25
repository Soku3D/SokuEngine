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
    float eta;
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
          alpha(0.0f),
          eta(0.0f) {}
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
        Hit hit(-1.0f, Vec3f(0.0f), Vec3f(0.0f));
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
class Triangle : public Shape {
  public:
    Vec3f v0, v1, v2;
    Vec2f uv0, uv1, uv2;
    Vec3f v01, v12, v20;
    Triangle(const Vec3f& v0, const Vec3f& v1, const Vec3f& v2,
             const Vec3f& color = Vec3f(0.0f))
        : v0(v0), v1(v1), v2(v2), Shape(color) {
        v01 = v1 - v0;
        v12 = v2 - v1;
        v20 = v0 - v2;
    }
    bool TriangleRayCollision(const Ray& ray, float& d, Vec3f& point,
                              Vec3f& normal, Vec2f& uv) {
        Vec3f normalVec = cross(v01, -v20);
        float areaX2 = GetLen(normalVec);
        normal = normalize(normalVec);

        if (std::abs(dot(normal, ray.d)) < 1e-5f) return false;

        if (dot(-normal, ray.d) < 0.0f) return false;

        d = dot(v0 - ray.o, normal) / dot(ray.d, normal);

        if (d < 0.0f) return false;
        point = ray(d);

        Vec3f v0p = point - v0;
        Vec3f v1p = point - v1;
        Vec3f v2p = point - v2;

        Vec3f cross0 = cross(v01, v0p);
        Vec3f cross1 = cross(v12, v1p);
        Vec3f cross2 = cross(v20, v2p);

        if (dot(cross0, normal) < 0.0f || dot(cross1, normal) < 0.0f ||
            dot(cross2, normal) < 0.0f)
            return false;

        float invAreaX2 = 1.0f / areaX2;

        uv = (GetLen(cross0) * invAreaX2) * uv2 +
             (GetLen(cross1) * invAreaX2) * uv0 +
             (GetLen(cross2) * invAreaX2) * uv1;
        return true;
    }
    virtual Hit CheckRayCollision(const Ray& ray) override {
        Hit hit(-1.0f, Vec3f(0.0f), Vec3f(0.0f));
        float d;
        Vec3f point, normal;
        Vec2f uv;
        if (TriangleRayCollision(ray, d, point, normal, uv)) {
            hit.normal = normal;
            hit.d = d;
            hit.point = point;
            hit.uv = uv;
        }
        return hit;
    }
};
class Rectangle : public Shape {
  public:
    Triangle tri0, tri1;
    Rectangle(const Vec3f& v0, const Vec3f& v1, const Vec3f& v2,
              const Vec3f& v3, const Vec3f& color = Vec3f(0.0f))
        : tri0(v0, v1, v2), tri1(v0, v2, v3) {
        tri0.uv0 = Vec2f(0.0f, 1.0f);
        tri0.uv1 = Vec2f(0.0f, 0.0f);
        tri0.uv2 = Vec2f(1.0f, 0.0f);

        tri1.uv0 = Vec2f(0.0f, 1.0f);
        tri1.uv1 = Vec2f(1.0f, 0.0f);
        tri1.uv2 = Vec2f(1.0f, 1.0f);
    }
    virtual Hit CheckRayCollision(const Ray& ray) override {
        Hit hit1 = tri0.CheckRayCollision(ray);
        Hit hit2 = tri1.CheckRayCollision(ray);

        if (hit1.d > 0.0f)
            return hit1;
        else {
            return hit2;
        }
    }
};

}  // namespace engine
#endif