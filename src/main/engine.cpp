#include "engine.h"
#include "geometry.h"
#include "renderer.h"
#include "texture.h"

 
int main() {
    
    int width = 1920*4, height = 1080*4;
    std::string buildPath = EXPAND(OUTPUT_PATH);
    std::string imgPath = buildPath + "/../src/textures/";
    std::string outputPath = buildPath + "/../Results/";
    std::cout << "Enter the file name to save : ";
    std::string filename;
    std::cin >> filename;
    
    engine::Raytracer raytracer(width, height);
    std::vector<engine::Vec3f> pixels(width * height);
    raytracer.Render(pixels);
    outputPath += filename + ".png";
    engine::Texture texture(pixels, width, height);

    //texture.SaveImage("test.png");
    texture.SaveImage(outputPath);

    system(outputPath.c_str());
  }
