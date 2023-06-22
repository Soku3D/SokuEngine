#pragma once
#include "engine.h"
#include "geometry.h"

namespace engine {
class Texture {
  public:
    std::vector<unsigned char> pixels;
    int width, height, channels;
    Texture(
        const std::vector<Vec3f>& img, int width, int height,
        int channels = 3);
    Texture(const char* imagePath);

    void SaveImage(const std::string& filename);
};
};  // namespace engin