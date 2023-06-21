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
};
template <typename T>
class Vector3 {
  public:
    T x, y, z;
    bool HasNaNs() const { return (isNaNs(x) || isNaNs(y) || isNaNs(z)); }
    Vector3() : x(0), y(0), z(0){};
    Vector3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) { assert(!HasNaNs()); }
    Vector3(T val) : x(val), y(val), z(val) { assert(!HasNaNs()); }
    T operator[](int idx) const {
        assert(idx > -1 && idx < 3);
        if (idx == 0) return x;
        if (idx == 1) return y;
        return z;
    }
    T& operator[](int idx) {
        assert(idx > -1 && idx < 2);
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
        return Vector3<T>(x + v.x, y + v.y, z + v.z);
    }
    Vector3<T>& operator-=(const Vector3<T>& v) {
        x += v.x;
        y += v.y;
        z += v.z;
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
    Vector3<T>& operator-() {
        x = -x;
        y = -y;
        z = -z;
        return *this;
    }
   	bool operator==(const Vector3<T>& v) const{
   		return (x==v.x && y == v.y && z ==v.z);
   	}
   	float& GetLen() const{
   		return std::sqrt((double)x*x + (double)y*y + (double)z*z);
   	}
   	
};
template <typename T>
std::ostream& operator<<(std::ostream& out, Vector3<T>& v) {
    out << '[' << v.x << ", " << v.y << ", " << v.z << ']' << '\n';
    return out;
}
template <typename T>
inline Vector3<T> operator*(T s, const Vector3<T>& v) {
    return v*s;
}
template <typename T>
inline T dot(const Vector3<T>& v1, const Vector3<T>& v2) {
    return (v1.x* v2.x + v1.y *v2.y + v1.z*v2.z);
}
template <typename T>
inline Vector3<T>& cross(const Vector3<T>& v1, const Vector3<T>& v2) {
    double x = (double)v1.y*v2.z - (double)v1.z*v2.y;
    double y = (double)v1.z*v2.x - (double)v1.x*v2.z;
    double z = (double)v1.x*v2.y - (double)v1.y*v2.x;

    return Vector3<T>(x,y,z);
}
template <typename T> inline
float GetLen(const Vector3<T>& v){
   	return std::sqrt((double)v.x*v.x + (double)v.y*v.y + (double)v.z*v.z);
}
template <typename T> inline
Vector3<T>& nomalization(Vector3<T>& v){
   float len = GetLen(v);
   assert(len);
   double inv = 1.0 / len;
   v.x*=inv;v.y*=inv;v.z*=inv;
   return v;
}
typedef Vector3<int> Vec3i;
typedef Vector3<float> Vec3f;

template <typename T>
class Normal3{
public:
	T x,y,z;
	explicit Normal3(Veector3<T>& v)
	:x(v.x) ,y(v.y), z(v.z){}
}

class Ray{
public:
	Ray() : o(0.0f), d(0.0f), tMax(Infinity){
		assert(!HasNaNs());
	}
	Ray(const Vec3f& o,const Vec3f& d, float tMax = infinity)
	:o(o), d(d), tMax(tMax){
		assert(!HasNaNs());
	}
	Vec3f operator()(float t) const {
		return (o+t*d);
	}
	bool HasNaNs() { return (o.HasNaNs() || d.HasNaNs() || isNaNs(tMax));}
	vec3f o, d;
	mutable float tMax;
}
}  // namespace engine
