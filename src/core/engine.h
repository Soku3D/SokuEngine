#pragma once
#include <type_traits>
#include <algorithm>
#include <cinttypes>
#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <vector>
#include <assert.h>
#include <string.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>

#define MaxFloat std::numeric_limits<float>::max()
#define Infinity std::numeric_limits<float>::infinity()

template<typename T>
class Vector2;
template<typename T>
class Vector3;
template <typename T>
class Normal3;
template <typename T>
class BoundingBox2;
template <typename T>
class BoundingBox3;
class Ray;

