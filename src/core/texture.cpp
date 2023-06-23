#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include "texture.h"

namespace engine {
Texture::Texture(const std::vector<Vec3f>& img, int width, int height,
                 int channels)
    : width(width), height(height), channels(channels) {
    buildPath = EXPAND(OUTPUT_PATH);
    pixels.resize(width * height * channels);
    for (size_t i = 0; i < width * height; i++) {
        pixels[i * channels] = static_cast<unsigned char>(img[i].x * 255.0f);
        pixels[i * channels + 1] =
            static_cast<unsigned char>(img[i].y * 255.0f);
        pixels[i * channels + 2] =
            static_cast<unsigned char>(img[i].z * 255.0f);
    }
}
Texture::Texture(std::string imagePath) {
    buildPath = EXPAND(OUTPUT_PATH);
    buildPath += "/../src/textures/" + imagePath;

    unsigned char* img =
        stbi_load(buildPath.c_str(), &width, &height, &channels, 0);

    pixels.resize(width * height * channels);
    memcpy(pixels.data(), img, pixels.size() * sizeof(uint8_t));
    delete[] img;
}
Vec3f Texture::GetClamped(int i, int j) { 
    i = clamp(i, 0, width - 1);
    j = clamp(j, 0, height - 1);
    int idx = (i + j * width) * channels;
    float r = pixels[idx] / 255.0f;
    float g = pixels[idx + 1] / 255.0f;
    float b = pixels[idx + 2] / 255.0f;
    
    return Vec3f(r, g, b);
}
Vec3f Texture::GetWrappedVec(const Vec2i v) { 
    return GetClamped(v.x, v.y); 
}

Vec3f Texture::GetWrapped(int i, int j) {
    i += width;
    j += height;
    i = clamp(i, 0, width - 1);
    j = clamp(j, 0, height - 1);
    int idx = (i + j * width) * channels;
    float r = pixels[idx] / 255.0f;
    float g = pixels[idx + 1] / 255.0f;
    float b = pixels[idx + 2] / 255.0f;

    return Vec3f(r, g, b);
}
Vec3f Texture::GetClampedVec(const Vec2i v) { 
    return GetWrapped(v.x, v.y); 
}

Vec3f Texture::SamplePoint(const Vec2f& uv) {
    Vec2f texturePos = TransformUvToTexture(uv);
    int i = std::round(texturePos.x);
    int j = std::round(texturePos.y);
    return GetClamped(i, j);
}
Vec3f Texture::SampleLinear(const Vec2f& uv) {
    Vec2f texturePos = TransformUvToTexture(uv);
    int i = std::floor(texturePos.x);
    int j = std::floor(texturePos.y);
    Vec2i pos00(i, j);
    Vec2i pos10(i+1, j);
    Vec2i pos01(i, j+1);
    Vec2i pos11(i+1, j+1);

    float wx0 = texturePos.x -i;
    float wx1 = 1.0f - wx0;
    float wy0 = texturePos.y - j;
    float wy1 = 1.0f - wy0;

    Vec3f LinearColor0 = GetWrappedVec(pos00) * wx1 + GetWrappedVec(pos10) * wx0;
    Vec3f LinearColor1 = GetWrappedVec(pos01) * wx1 + GetWrappedVec(pos11) * wx0;

    return (LinearColor0*wy1 + LinearColor1* wy0);
}
Vec2f Texture::TransformUvToTexture(const Vec2f& uv) {
    float xPos = width * uv.x - 0.5f;
    float yPos = height * uv.y - 0.5f;
    return Vec2f(xPos, yPos);
}

void Texture::SaveImage(const std::string& filename) {
    stbi_write_png(filename.c_str(), width, height, channels, pixels.data(),
                   width * channels);
}
}  // namespace engine
