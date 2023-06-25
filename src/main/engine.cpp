#include "engine.h"
#include "geometry.h"
#include "renderer.h"
#include "texture.h"

 
int main() {
    
    int width = 1920, height = 1080;
    std::string buildPath = EXPAND(OUTPUT_PATH);
    std::string imgPath = buildPath + "/../src/textures/";
    std::string outputPath = buildPath + "/../Results/";
    std::cout << "Enger the chapter: ";
    int chapter;
    std::cin >> chapter;

    std::cout << "Enter the file name to save : ";

    std::string filename;
    std::cin >> filename;
    
    //engine::Raytracer raytracer(width, height);
    engine::Rasterization rasterization(width, height);
    std::vector<engine::Vec3f> pixels(width * height);

    //raytracer.Render(pixels);
    rasterization.Render(pixels);

    outputPath += "chap" + std::to_string(chapter) + '\\' + filename + ".png ";

    std::cout << outputPath;
    engine::Texture texture(pixels, width, height);

    //texture.SaveImage("test.png");
    texture.SaveImage(outputPath);

    system(outputPath.c_str());
  }
