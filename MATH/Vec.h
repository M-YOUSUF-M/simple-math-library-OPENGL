#pragma once
struct vec3 {
	float x, y, z;
	vec3(float x = 0, float y = 0, float z = 0) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	vec3 operator+(const vec3& vec) const {
		return vec3(
			x + vec.x,
			y + vec.y,
			z + vec.z
		);
	}
	vec3 operator-(const vec3& vec)const {
		return vec3(
			x - vec.x,
			y - vec.y,
			z - vec.z
		);
	}
	float dot(const vec3& other)const {
		return 
			x * other.x +
			y * other.y + 
			z * other.z
		;
	}

	vec3 cross(const vec3& other)const {
		return vec3(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x
		);
	}

	vec3 normalize() {
		float magnaturte = sqrt(x * x + y * y + z * z);

		this->x /= magnaturte;
		this->y /= magnaturte;
		this->z /= magnaturte;
		return* this;
	}
};
