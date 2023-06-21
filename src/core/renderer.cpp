#include "renderer.h"
namespace engine {
void Raytracer::Render(std::vector<Vec3f>& pixels) {
    std::fill(pixels.begin(), pixels.end(), Vec3f(0.0f));
#pragma omp parallel for
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
        }
    }
}
}  // namespace engine