#pragma once
#include "engine.h"

template <typename T>
inline bool isNaNs(const T val) {
    return std::isnan(val);
}
template <>
inline bool isNaNs(const int val) {
    return false;
}
namespace engine {

template <typename T>
class Vector2 {
  public:
    T x, y;
    bool HasNaNs() const { return isNaNs(x) || isNaNs(y); }

    Vector2() : x(0), y(0){};
    Vector2(T xx, T yy) : x(xx), y(yy) { assert(!HasNaNs()); }
    T operator[](int idx) const {
        assert(idx > -1 && idx < 2);
        if (idx == 0) return x;
        return y;
    }
    T& operator[](int idx) {
        assert(idx > -1 && idx < 2);
        if (idx == 0) return x;
        return y;
    }
    Vector2<T> operator+(const Vector2<T>& v) const {
        return Vector2<T>(x + v.x, y + v.y);
    }
    Vector2<T>& operator+=(const Vector2<T>& v) {
        x += v.x;
        y += v.y;
        return *this;
    }
    Vector2<T> operator-(const Vector2<T>& v) const {
        return Vector2<T>(x - v.x, y - v.y);
    }
    Vector2<T>& operator-=(const Vector2<T>& v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }
    Vector2<T> operator*(T v) const { return Vector2<T>(x * v, y * v); }
    Vector2<T>& operator*=(T v) {
        x *= v;
        y *= v;
        return *this;
    }
    Vector2<T> operator/(T v) const {
        assert(v != 0);
        float inv = 1.0f / v;
        return Vector2<T>(x * inv, y * inv);
    }
    Vector2<T>& operator/=(T v) {
        assert(v != 0);
        float inv = 1.0f / v;
        x *= inv;
        y *= inv;
        return *this;
    }
    Vector2<T> operator-() {
        Vector2<T> v(-x, -y, -z); 
        return v;
    }
    bool operator==(const Vector2<T>& v) const {
        return (x == v.x && y == v.y);
    }
    friend std::ostream& operator<<(std::ostream& out, Vector2<T>& v) {
        out << '[' << v.x << ", " << v.y << ']' << '\n';
        return out;
    }
};
template <typename T>
class Vector3 {
  public:
    T x, y, z;
    bool HasNaNs() const { return (isNaNs(x) || isNaNs(y) || isNaNs(z)); }
    Vector3() { x = y = z = 0; }
    Vector3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) { assert(!HasNaNs()); }
    Vector3(T val) : x(val), y(val), z(val) { assert(!HasNaNs()); }
    T operator[](int idx) const {
        assert(idx >= 0 && idx <= 2);
        if (idx == 0) return x;
        if (idx == 1) return y;
        return z;
    }
    T& operator[](int idx) {
        assert(idx >= 0 && idx <= 2);
        if (idx == 0) return x;
        if (idx == 1) return y;
        return z;
    }
    Vector3<T> operator+(const Vector3<T>& v) const {
        return Vector3<T>(x + v.x, y + v.y, z + v.z);
    }
    Vector3<T>& operator+=(const Vector3<T>& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }
    Vector3<T> operator-(const Vector3<T>& v) const {
        return Vector3<T>(x - v.x, y - v.y, z - v.z);
    }
    Vector3<T>& operator-=(const Vector3<T>& v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }
    Vector3<T> operator*(T v) const { return Vector3<T>(x * v, y * v, z * v); }
    Vector3<T>& operator*=(T v) {
        x *= v;
        y *= v;
        z *= v;
        return *this;
    }
    
    Vector3<T> operator/(T v) const {
        assert(v != 0);
        float inv = 1.0f / v;
        return Vector3<T>(x * inv, y * inv, z * inv);
    }
    Vector3<T>& operator/=(T v) {
        assert(v != 0);
        float inv = 1.0f / v;
        x *= inv;
        y *= inv;
        z *= inv;
        return *this;
    }
    Vector3<T> operator-() {
        Vector3<T> v(-x, -y, -z);
        return v;
    }
    bool operator==(const Vector3<T>& v) const {
        return (x == v.x && y == v.y && z == v.z);
    }
    float& GetLen() const {
        return std::sqrt((double)x * x + (double)y * y + (double)z * z);
    }
};
template <typename T>
std::ostream& operator<<(std::ostream& out, Vector3<T>& v) {
    out << '[' << v.x << ", " << v.y << ", " << v.z << ']' << '\n';
    return out;
}

template <typename T>
inline Vector3<T> operator*(T s, const Vector3<T>& v) {
    return v * s;
}
template <typename T>
inline Vector2<T> operator*(T s, const Vector2<T>& v) {
    return v * s;
}
template <typename T>
inline T dot(const Vector3<T>& v1, const Vector3<T>& v2) {
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}
template <typename T>
inline Vector3<T>& cross(const Vector3<T>& v1, const Vector3<T>& v2) {
    double x = (double)v1.y * v2.z - (double)v1.z * v2.y;
    double y = (double)v1.z * v2.x - (double)v1.x * v2.z;
    double z = (double)v1.x * v2.y - (double)v1.y * v2.x;

    return Vector3<T>(x, y, z);
}
template <typename T>
inline float GetLen(const Vector3<T>& v) {
    return static_cast<float>(std::sqrt((double)v.x * v.x + (double)v.y * v.y + (double)v.z * v.z));
}
template <typename T>
inline Vector3<T> normalize(Vector3<T> v) {
    float len = GetLen(v);
    assert(len);
    double inv = 1.0 / len;
    v.x *= inv;
    v.y *= inv;
    v.z *= inv;
    return v;
}
template <typename T>
inline T clamp(T val, T min, T max) {
    if (val < min) return min;
    if (val > max) return max;
    return val;
}
template <typename T>
inline Vector3<T> clamp(Vector3<T> val, Vector3<T> min, Vector3<T> max) {
    Vector3<T> ret = val;
    for (int i = 0; i < 3; i++) {
        ret[i] = clamp(val[i], min[i], max[i]);
    }
    return ret;
}
typedef Vector3<int> Vec3i;
typedef Vector3<float> Vec3f;
typedef Vector2<int> Vec2i;
typedef Vector2<float> Vec2f;

template <typename T>
class Normal3 {
  public:
    T x, y, z;
    explicit Normal3(Vector3<T>& v) : x(v.x), y(v.y), z(v.z) {}
};

class Ray {
  public:
    Ray() : o(0.0f), d(0.0f), tMax(Infinity) { assert(!HasNaNs()); }
    Ray(const Vec3f& o, const Vec3f& d, float tMax = Infinity)
        : o(o), d(d), tMax(tMax) {
        assert(!HasNaNs());
    }
    Vec3f operator()(float t) const { return (o + t * d); }
    bool HasNaNs() { return (o.HasNaNs() || d.HasNaNs() || isNaNs(tMax)); }
    Vec3f o, d;
    mutable float tMax;
};
template <typename T>
class BoundingBox2 {
  public:
    Vector2<T> pMin, pMax;
    BoundingBox2() {
        pMin = Vector2(std::numeric_limits<T>::max());
        pMax = Vector2(std::numeric_limits<T>::lowest());
    }
    BoundingBox2(const Vector2<T>& p) : pMin(p), pMax(p) {}
    BoundingBox2(const Vector2<T>& p1, const Vector2<T>& p2)
        : pMin(std::min(p1.x, p2.x), std::min(p1.y, p2.y)),
          pMax(std::max(p1.x, p2.x), std::max(p1.y, p2.y))
    {}
};
template <typename T>
class BoundingBox3 {
  public:
    // DirectX::XMFLOAT3 pMin, pMax;
    Vector3<T> pMin, pMax;
    BoundingBox3() {
        pMin = Vector3<T>(std::numeric_limits<T>::max());
        pMax = Vector3<T>(std::numeric_limits<T>::lowest());
    }
};
typedef BoundingBox2<float> bounds2f;
typedef BoundingBox3<float> bounds3f;

template <typename T>
BoundingBox2<T> Union() {
    return BoundingBox2<T>(0.0f);
}
template <typename T>
bool overlaps() {
    return BoundingBox2<T>(0.0f);
}

}  // namespace engine
