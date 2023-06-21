#include "engine.h"
#include "renderer.h"
#include "geometry.h"
using namespace engine;
int main(){
    int width = 1920, height = 1080;
    std::vector<Vec3f> pixels;
    pixels.resize(width * height);
    Raytracer raytracer(width, height);
    raytracer.Render(pixels);
}