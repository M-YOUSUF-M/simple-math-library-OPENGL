#pragma once
#include <math.h>
#include "Vec.h"

struct Mat4
{
	float mat[4 * 4];
	Mat4() {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (i == j) {
					mat[4 * i + j] = 1;
				}
				else {
					mat[4 * i + j] = 0;
				}
			}
		}
	}
	Mat4 multiply(Mat4& matB) {
		Mat4 resultMatrix;
		for (int row = 0; row < 4; ++row) {
			for (int col = 0; col < 4; ++col) {
			    resultMatrix.mat[col * 4 + row] = 0; 
				for (int k = 0; k < 4; ++k) {
                resultMatrix.mat[col * 4 + row] += this->mat[k * 4 + row] * matB.mat[col * 4 + k];
				}
			}
		}
		return resultMatrix;
	}
	Mat4 scale(const vec3& scaleFactor) const {
		Mat4 scaleMatrix;
		scaleMatrix.mat[0] *= scaleFactor.x;
		scaleMatrix.mat[5] *= scaleFactor.y;
		scaleMatrix.mat[10] *= scaleFactor.z;
		return scaleMatrix;
	}

	Mat4 translationMatrixf(vec3& shift_position ) {
		Mat4 translateMatrix;
		translateMatrix.mat[3] = shift_position.x;
		translateMatrix.mat[7] = shift_position.y;
		translateMatrix.mat[11] = shift_position.z;
		return translateMatrix;
	}

	Mat4 rotationXaxisf(float theta) {
		Mat4 rotationMatrix;
		rotationMatrix.mat[5] = cosf(theta);
		rotationMatrix.mat[6] = -sinf(theta);
		rotationMatrix.mat[9] = sinf(theta);
		rotationMatrix.mat[10] = cosf(theta);
		return rotationMatrix;
	}
	Mat4 rotationYaxisf(float theta) {
		Mat4 rotationMatrix;
		rotationMatrix.mat[0] = cosf(theta);
		rotationMatrix.mat[2] = sinf(theta);
		rotationMatrix.mat[8] = -sinf(theta);
		rotationMatrix.mat[10] = cosf(theta);
		return rotationMatrix;
	}
	Mat4 rotationZaxisf(float theta) {
		Mat4 rotationMatrix;
		rotationMatrix.mat[0] = cosf(theta);
		rotationMatrix.mat[1] = -sinf(theta);
		rotationMatrix.mat[4] = sinf(theta);
		rotationMatrix.mat[5] = cosf(theta);
		return rotationMatrix;
	}

	Mat4 perspective(float fov, float aspectRatio, float nearPlane, float farPlane) {
		Mat4 projectionMatrix;
    
		float tanHalfFOV = tanf(fov / 2.0f);
		float range = nearPlane - farPlane;

		projectionMatrix.mat[0] = 1.0f / (aspectRatio * tanHalfFOV);
		projectionMatrix.mat[5] = 1.0f / tanHalfFOV;
		projectionMatrix.mat[10] = -(nearPlane + farPlane) / range;
		projectionMatrix.mat[11] = -1.0f;
		projectionMatrix.mat[14] = (2.0f * nearPlane * farPlane) / range;
		projectionMatrix.mat[15] = 0.0f;

		return projectionMatrix;
	}

	Mat4 lookAt(const vec3& eye, const vec3& center, const vec3& up) {
    vec3 f = (center - eye).normalize();   // Forward direction
    vec3 s = f.cross(up).normalize();      // Right direction
    vec3 u = s.cross(f);                   // Up direction

    Mat4 viewMatrix;
    viewMatrix.mat[0] = s.x;
    viewMatrix.mat[1] = u.x;
    viewMatrix.mat[2] = -f.x;
    viewMatrix.mat[4] = s.y;
    viewMatrix.mat[5] = u.y;
    viewMatrix.mat[6] = -f.y;
    viewMatrix.mat[8] = s.z;
    viewMatrix.mat[9] = u.z;
    viewMatrix.mat[10] = -f.z;
    viewMatrix.mat[12] = -s.dot(eye);
    viewMatrix.mat[13] = -u.dot(eye);
    viewMatrix.mat[14] = f.dot(eye);
    viewMatrix.mat[15] = 1.0f;

    return viewMatrix;
}


};