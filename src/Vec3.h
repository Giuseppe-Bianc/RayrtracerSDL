#pragma once
#include "headers.h"
class Vec3 {
public:
	Vec3() = default;
	Vec3(double x, double y, double z);
	double x() const;
	double y() const;
	double z() const;
	Vec3 operator-() const;
	double operator[](int i) const;
	double& operator[](int i);
	Vec3& operator+=(const Vec3& v);
	Vec3& operator*=(const double t);
	Vec3& operator/=(const double t);
	double length() const;
	//~vec3();
	inline friend std::ostream& operator<<(std::ostream& out, const Vec3& v);
	inline friend Vec3 operator+(const Vec3& u, const Vec3& v);
	inline friend Vec3 operator-(const Vec3& u, const Vec3& v);
	inline friend Vec3 operator*(const Vec3& u, const Vec3& v);
	inline friend Vec3 operator*(double t, const Vec3& v);
	inline friend Vec3 operator*(const Vec3& v, double t);
	inline friend Vec3 operator/(Vec3 v, double t);
	inline friend double dot(const Vec3& u, const Vec3& v);
	inline friend Vec3 cross(const Vec3& u, const Vec3& v);
	inline friend Vec3 unit_vector(Vec3 v);

private:
	glm::dvec3 e;
};

using point3 = Vec3;   // 3D point
using color = Vec3;    // RGB color
