#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include "texture.h"

namespace engine {
Texture::Texture(const std::vector<Vec3f>& img, int width,
                          int height, int channels)
    :width(width),height(height),channels(channels) {
    
    pixels.resize(width * height * channels);
    for (size_t i = 0; i < width*height; i++) {
        pixels[i * channels] = static_cast<unsigned char>(img[i].x * 255.0f);
        pixels[i * channels+1] = static_cast<unsigned char>(img[i].y * 255.0f);
        pixels[i * channels+2] = static_cast<unsigned char>(img[i].z * 255.0f);
    }
}
Texture::Texture(const char* imagePath) {
    unsigned char* img = stbi_load(imagePath, &width, &height, &channels, 0);
    
    pixels.resize(width * height * channels);
    memcpy(pixels.data(), img, pixels.size() * sizeof(uint8_t));
    delete[] img;
}

void Texture::SaveImage(const std::string& filename) {
    stbi_write_png(filename.c_str(), width, height, channels, pixels.data(),
                   width * channels);
}
}  // namespace engine
