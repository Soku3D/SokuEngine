#pragma once
#include "engine.h"
#include "geometry.h"

namespace engine {
class Texture {
  public:
    std::vector<unsigned char> pixels;
    int width, height, channels;
    Texture(const std::vector<Vec3f>& img, int width, int height,
            int channels = 3);
    Texture(std::string imagePath);
    std::string buildPath;
    
    Vec3f GetWrapped(int i, int j);
    Vec3f GetWrappedVec(const Vec2i v);

    Vec3f GetClamped(int i, int j);
    Vec3f GetClampedVec(const Vec2i v);



    Vec3f SamplePoint(const Vec2f& uv);
    Vec3f SampleLinear(const Vec2f& uv);

    Vec2f TransformUvToTexture(const Vec2f& uv);
    void SaveImage(const std::string& filename);
};
};  // namespace engine