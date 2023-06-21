#include "engine.h"
#include "geometry.h"

using namespace engine;
int main(){

    Vec3f v1(2.0f, 1.0f, 3.0f);
    Vec3f v2(2.0f, 0.0f, 0.0f);
    Vec3f v3 = cross(v1, v2);
    std::cout <<v3;
    v3 = cross(v2, v1);
    std::cout << v3;
    std::cout << MaxFloat << ' ' << Infinity;   
}