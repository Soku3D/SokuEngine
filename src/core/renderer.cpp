#include "renderer.h"

#include <algorithm>
namespace engine {

Raytracer::Raytracer(int width, int height)
    : width(width),
      height(height),
      invW(1.0f / (width - 1)),
      invH(1.0f / (height - 1)),
      light(Vec3f(2.0f, 3.0f, -1.0f)) {
    aspect = (float)width / height;

    std::shared_ptr<Texture> backgroundTexture =
        std::make_shared<Texture>("background.png");
    std::shared_ptr<Texture> customTexture =
        std::make_shared<Texture>("custom.png");

    std::shared_ptr<Sphere> reflectiveSphere1 =
        std::make_shared<Sphere>(Vec3f(3.0f, -1.3f, 3.0f), 1.3f);
    reflectiveSphere1->reflection = 0.4f;
    reflectiveSphere1->amb = Vec3f(0.4f);
    reflectiveSphere1->dif = Vec3f(0.8f, 0.2f, 0.2f);
    reflectiveSphere1->spec = Vec3f(1.0f);
    reflectiveSphere1->ks = 10.0f;
    reflectiveSphere1->alpha = 100.0f;

    std::shared_ptr<Sphere> reflectiveSphere2 =
        std::make_shared<Sphere>(Vec3f(-3.0f, -1.3f, 3.0f), 1.3f);

    reflectiveSphere2->amb = Vec3f(0.4f);
    reflectiveSphere2->dif = Vec3f(0.2f, 0.8f, 0.2f);
    reflectiveSphere2->spec = Vec3f(1.0f);
    reflectiveSphere2->reflection = 0.4f;
    reflectiveSphere2->ks = 10.0f;
    reflectiveSphere2->alpha = 100.0f;

    std::shared_ptr<Sphere> reflectiveSphere3 =
        std::make_shared<Sphere>(Vec3f(0.0f, 1.5f, 3.0f), 1.3f);
    reflectiveSphere3->reflection = 0.4f;
    reflectiveSphere3->amb = Vec3f(0.4f);
    reflectiveSphere3->dif = Vec3f(0.2f, 0.2f, 0.8f);
    reflectiveSphere3->spec = Vec3f(1.0f);
    reflectiveSphere3->ks = 10.0f;
    reflectiveSphere3->alpha = 100.0f;

    std::shared_ptr<Sphere> reflectiveSphere4 =
        std::make_shared<Sphere>(Vec3f(3.0f, 1.5f, 3.0f), 1.3f);
    reflectiveSphere4->reflection = 0.4f;
    reflectiveSphere4->amb = Vec3f(0.4f);
    reflectiveSphere4->dif = Vec3f(0.3f, 0.9f, 0.8f);
    reflectiveSphere4->spec = Vec3f(1.0f);
    reflectiveSphere4->ks = 10.0f;
    reflectiveSphere4->alpha = 100.0f;

    std::shared_ptr<Sphere> transparentSphere =
        std::make_shared<Sphere>(Vec3f(0.0f, -1.3f, 3.0f), 1.3f);
    transparentSphere->transparency = 1.0f;
    transparentSphere->eta = 1.52f;

    std::shared_ptr<Sphere> transparentSphere2 =
        std::make_shared<Sphere>(Vec3f(-3.0f, 1.5f, 3.0f), 1.3f);
    transparentSphere2->transparency = 1.0f;
    transparentSphere2->eta = 1.3f;

    auto triangle = std::make_shared<Triangle>(Vec3f(-2.0f, -2.0f, 1.0f),
                                               Vec3f(-2.0f, 2.0f, 1.0f),
                                               Vec3f(2.0f, 2.0f, 1.0f));
    triangle->amb = Vec3f(0.4f);
    triangle->dif = Vec3f(0.8f);
    triangle->spec = Vec3f(1.0f);
    triangle->ks = 10.0f;
    triangle->alpha = 100.0f;

    auto background = std::make_shared<Rectangle>(
        Vec3f(-6.0f * aspect, -6.0f, 5.0f), Vec3f(-6.0f * aspect, 6.0f, 5.0f),
        Vec3f(6.0f * aspect, 6.0f, 5.0f), Vec3f(6.0f * aspect, -6.0f, 5.0f));
    background->amb = Vec3f(1.0f);
    background->dif = Vec3f(0.0f);
    background->spec = Vec3f(0.0f);
    background->ks = 10.0f;
    background->alpha = 100.0f;
    background->ambTexture = backgroundTexture;

    /*auto background = std::make_shared<Rectangle>(
        Vec3f(-3.0f , -3.0f, 5.0f), Vec3f(-3.0f , 3.0f, 5.0f),
        Vec3f(3.0f ,3.0f, 5.0f), Vec3f(3.0f, -3.0f, 5.0f));
    background->amb = Vec3f(1.0f);
    background->dif = Vec3f(0.0f);
    background->spec = Vec3f(0.0f);
    background->ks = 10.0f;
    background->alpha = 100.0f;*/

    auto floor = std::make_shared<Rectangle>(
        Vec3f(-8.0f, -3.0f, 1.0f), Vec3f(-8.0f, -3.0f, 5.0f),
        Vec3f(8.0f, -3.0f, 5.0f), Vec3f(8.0f, -3.0f, 1.0f));
    floor->amb = Vec3f(1.0f);
    floor->reflection = 0.4;
    floor->ambTexture = customTexture;

    // shapes.push_back(transparentSphere);
    // shapes.push_back(transparentSphere2);

    // shapes.push_back(reflectiveSphere1);
    // shapes.push_back(reflectiveSphere2);
    // shapes.push_back(reflectiveSphere3);
    shapes.push_back(reflectiveSphere4);

    // shapes.push_back(floor);
    //  shapes.push_back(triangle);
    shapes.push_back(background);

    eyePos = Vec3f(0.0f, 0.0f, -1.5f);
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
bool Raytracer::IsShadow(const Ray& ray) {
    Hit hit = FindClosestShape(ray);
    if (hit.d >= 0.0f) return true;
    return false;
}
Vec3f Raytracer::traceRay(const Ray& ray, int recurseLevel) {
    Hit hit = FindClosestShape(ray);

    if (recurseLevel < 0) return Vec3f(0.0f);
    if (hit.d >= 0.0f) {
        Vec3f ambColor(0.0f);
        Vec3f difColor(0.0f);
        Vec3f specColor(0.0f);

        Vec3f LightDirection = normalize(hit.point - light.pos);
        float dif = clamp(dot(-LightDirection, hit.normal), 0.0f, 1.0f);

        if (hit.pShape->ambTexture) {
            Vec3f TextureColor = hit.pShape->ambTexture->SampleLinear(hit.uv);
            ambColor = Vec3f(hit.pShape->amb.x * TextureColor.x,
                             hit.pShape->amb.y * TextureColor.y,
                             hit.pShape->amb.z * TextureColor.z);
        } else {
            ambColor = hit.pShape->amb;
        }
        /* Ray LigthRay(-LightDirection * 1e-4f + hit.point, -LightDirection);
         if (IsShadow(LigthRay)) {
             return ambColor;
         }*/
        if (hit.pShape->difTexture) {
        } else {
            difColor = hit.pShape->dif * dif;
        }
        Vec3f reflectDir =
            2.0f * dot(-LightDirection, hit.normal) * hit.normal +
            LightDirection;
        float spec = std::pow(clamp(-dot(reflectDir, ray.d), 0.0f, 1.0f),
                              hit.pShape->alpha);
        Vec3f color =
            ambColor + difColor + spec * hit.pShape->spec * hit.pShape->ks;

        float colorScale =
            1.0f - hit.pShape->transparency - hit.pShape->reflection;

        color *= colorScale;
        if (hit.pShape->reflection) {
            Vec3f reflectionDir =
                (2.0f * dot(-hit.normal, ray.d)) * hit.normal + ray.d;
            Ray reflectionRay(hit.point + reflectionDir * 1e-4f, reflectionDir);
            color += traceRay(reflectionRay, recurseLevel - 1) *
                     hit.pShape->reflection;
        }
        if (hit.pShape->transparency) {
            Vec3f normal = hit.normal;
            float rEta = 1.0f / hit.pShape->eta;
            if (dot(hit.normal, ray.d) >= 0.0f) {
                normal = -normal;
                rEta = hit.pShape->eta;
            }
            float cosTheta1 = dot(ray.d, normal);
            float sinTheta1Double = 1.0f - cosTheta1 * cosTheta1;
            float sinTheta2Double = rEta * rEta * sinTheta1Double;
            float cosTheta2 = std::sqrt(1.0f - sinTheta2Double);

            Vec3f transmissionDir =
                (rEta)*ray.d + (rEta * cosTheta1 - cosTheta2) * normal;
            Ray transmittedRay(hit.point + transmissionDir * 1e-4f,
                               transmissionDir);
            color += traceRay(transmittedRay, recurseLevel - 1) *
                     hit.pShape->transparency;
        }
        return color;
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
    for (int x = 0; x < 2; x++) {
        for (int y = 0; y < 2; y++) {
            Vec3f newPos = currPos + Vec3f(subD * x, subD * y, 0.0f);
            color += traceRay2x2(newPos, subD, recursiveLevel - 1) * 0.25;
        }
    }
    return color;
}
void Raytracer::Render(std::vector<Vec3f>& pixels) {
    std::fill(pixels.begin(), pixels.end(), Vec3f(0.0f));
    // #pragma omp parallel for
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Vec3f worldPos = TransformScreenToWorld(x, y);
            // std::cout << worldPos << '\n';
            float d = 2.0f * invH;
            pixels[y * width + x] =
                clamp(traceRay2x2(worldPos, d, 0), Vec3f(0.0f), Vec3f(1.0f));
            // std::cout << x << ' ' << y << '\n';
        }
    }
}
Vec3f Raytracer::TransformScreenToWorld(int x, int y) {
    float xScale = invW * 2.0f;
    float yScale = invH * 2.0f;
    float X = (x * xScale - 1.0f) * aspect;
    float Y = y * yScale - 1.0f;
    return Vec3f(X, -Y, 0.0f);
}
Rasterization::Rasterization(const int& width, const int& height)
    : width(width), height(height), aspect((float)width / height) {
    vertecies[0] = Vec3f(0.0f, 0.5f, 1.0f);
    vertecies[1] = Vec3f(1.0f, -0.5f, 1.0f);
    vertecies[2] = Vec3f(-1.0f, -0.5f, 1.0f);
}
float Rasterization::CCW(const Vec2f& v0, const Vec2f& v1, const Vec2f& point) {
    Vec2f v01 = v1 - v0;
    Vec2f v0p = point - v0;

    return (v01.x * v0p.y - v01.y * v0p.x);
}
Vec2f Rasterization::ProjectWorldToScreen(Vec3f vertex) {
    
    Vec2f NDC = Vec2f(vertex.x / aspect, vertex.y);
    float xScale = (width-1) * 0.5f;
    float yScale = (1-height) * 0.5f;

    return Vec2f((NDC.x + 1) * xScale, (NDC.y-1)*yScale);
}
void Rasterization::Render(std::vector<Vec3f>& pixels) {

    const auto v0 = ProjectWorldToScreen(vertecies[0]);
    const auto v1 = ProjectWorldToScreen(vertecies[1]);
    const auto v2 = ProjectWorldToScreen(vertecies[2]);


    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            const Vec2f point = Vec2f(x, y);
            const float w0 = CCW(v0, v1, point);
            const float w1 = CCW(v1, v2, point);
            const float w2 = CCW(v2, v0, point);
            
            if (w0 >= 0.0f && w1 >= 0.0f && w2 >= 0.0f) {
                pixels[y * width + x] = Vec3f(1.0f);
            }
        }
    }
}
}  // namespace engine