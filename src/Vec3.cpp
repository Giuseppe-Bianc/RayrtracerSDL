#include "vec3.h"

Vec3::Vec3(double x, double y, double z) : e{x,y,z} {}

double Vec3::x() const { return e.x; }

double Vec3::y() const { return e.y; }

double Vec3::z() const { return e.z; }

Vec3 Vec3::operator-() const {
	return Vec3(-e.x, -e.y,-e.z);
}

double Vec3::operator[](int i) const{
	return e[i];
}

double& Vec3::operator[](int i){
	return e[i];
}

Vec3& Vec3::operator+=(const Vec3& v){
	e += v.e;
	return *this;
}

Vec3& Vec3::operator*=(const double t) {
	e *= t;
	return *this;
}

Vec3& Vec3::operator/=(const double t) {
	return *this *= 1 / t;
}

double Vec3::length() const{
	return glm::length(e);
}

inline Vec3 unit_vector(Vec3 v) {
	glm::dvec3 unit = glm::normalize(v.e);
	return Vec3(unit[0], unit[1], unit[2]);;
}

inline std::ostream& operator<<(std::ostream& out, const Vec3& v){

	return out << glm::to_string(v.e);
}

inline Vec3 operator+(const Vec3& u, const Vec3& v){
	return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline Vec3 operator-(const Vec3& u, const Vec3& v){
	return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline Vec3 operator*(const Vec3& u, const Vec3& v) {
	Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline Vec3 operator*(double t, const Vec3& v) {
	return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline Vec3 operator*(const Vec3& v, double t) {
	return t * v;
}

inline Vec3 operator/(Vec3 v, double t)
{
	return (1 / t) * v;
}

inline double dot(const Vec3& u, const Vec3& v){
	return glm::dot(u.e,v.e);
}

inline Vec3 cross(const Vec3& u, const Vec3& v){
	glm::dvec3 c = glm::cross(u.e, v.e);
	return Vec3(c[0],c[1],c[2]);
}