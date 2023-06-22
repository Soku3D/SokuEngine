#include "renderer.h"
#include <algorithm>
namespace engine {

Raytracer::Raytracer(int width, int height)
    : width(width), height(height), invW(1.0f / width), invH(1.0f / height),light(Vec3f(-2.0f, 2.0f, -3.0f)) {
    aspect = width * invH;
    std::shared_ptr<Sphere> sphere =
        std::make_shared<Sphere>(Vec3f(0.0f, 0.0f, 1.0f), 0.7f);
    sphere->amb = Vec3f(0.2f);
    sphere->dif = Vec3f(0.8f, 0.3f, 0.3f);
    sphere->spec = Vec3f(1.0f);
    sphere->ks = 10.0f;
    sphere->alpha = 100.0f;

    shapes.push_back(sphere);

    eyePos = Vec3f(0.0f, 0.0f, -1.0f);
}
Hit Raytracer::FindClosestShape(const Ray& ray) {
    Hit closestHit{-1.0f, Vec3f(0.0f), Vec3f(0.0f)};
    float closestD = 1e9f;

    for (size_t i = 0; i < shapes.size(); i++) {
        Hit hit = shapes[i]->CheckRayCollision(ray);
        if (hit.d >= 0.0f && hit.d < closestD) {
            closestD = hit.d;
            closestHit = hit;
            closestHit.pShape = shapes[i];
        }
    }
    return closestHit;
}
Vec3f Raytracer::traceRay(const Ray& ray, int recursiveLevel) {
    Hit hit = FindClosestShape(ray);
    if (hit.d >= 0.0f) {
        Vec3f ambColor(0.0f);
        Vec3f difColor(0.0f);
        Vec3f specColor(0.0f);

        Vec3f LightDirection = normalize(hit.point - light.pos);
        
        if (hit.pShape->ambTexture) {
        } else {
            ambColor = hit.pShape->amb;
        }
        if (hit.pShape->difTexture) {

        } else {           
            float dif = clamp(dot(-LightDirection, hit.normal), 0.0f, 1.0f);
            difColor = hit.pShape->dif * dif;
        }
        Vec3f reflectDir =
            2.0f * dot(-LightDirection, hit.normal) * hit.normal +
            LightDirection;
        float spec = std::pow(clamp(-dot(reflectDir, ray.d), 0.0f, 1.0f),
                              hit.pShape->alpha);
        return ambColor + difColor + spec*hit.pShape->spec * hit.pShape->ks;
    }
    return Vec3f(0.0f);
}
Vec3f Raytracer::traceRay2x2(const Vec3f& currPos, float currD,
                             int recursiveLevel) {
    if (recursiveLevel == 0) {
        Vec3f rayDir = normalize(currPos - eyePos);
        Ray ray(currPos, rayDir);
        return traceRay(ray, 5);
    }
    Vec3f color(0.0f);
    float subD = currD * 0.5f;
    Vec3f pixelPos = currPos - Vec3f(subD * 0.5f, subD * 0.5f, 0.0f);
}
void Raytracer::Render(std::vector<Vec3f>& pixels) {
    std::fill(pixels.begin(), pixels.end(), Vec3f(0.0f));
//#pragma omp parallel for
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Vec3f worldPos = TransformScreenToWorld(x, y);
            float d = 2.0f * invH;
            pixels[y * width + x] = clamp(traceRay2x2(worldPos, d, 0) , Vec3f(0.0f), Vec3f(1.0f));
            //std::cout << x << ' ' << y << '\n';
        }
    }
}
Vec3f Raytracer::TransformScreenToWorld(int x, int y) {
    float xScale = invW * 2.0f * aspect;
    float yScale = invH * 2.0f;
    float X = x * xScale - aspect;
    float Y = y * yScale - 1.0f;
    return Vec3f(X, -Y, 0.0f);
}

}  // namespace engine