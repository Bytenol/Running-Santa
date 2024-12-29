#pragma once
#ifndef __BYTENOL_RUNNING_SANTA_MAT4_H__
#define __BYTENOL_RUNNING_SANTA_MAT4_H__

#include <vector>
#include <cmath>


namespace mat4
{
	using tensor = std::vector<float>;

	tensor create();
	tensor translation(float tx, float ty, float tz);
	tensor xRotation(float angleInRadians);
	tensor yRotation(float angleInRadians);
	tensor zRotation(float angleInRadians);
	tensor scaling(float sx, float sy, float sz);
	tensor translate(const tensor& m, float tx, float ty, float tz);
	tensor multiply(const tensor& a, const tensor& b);
	tensor xRotate(const tensor& m, float angleInRadians);
	tensor yRotate(const tensor& m, float angleInRadians);
	tensor zRotate(const tensor& m, float angleInRadians);
	tensor scale(const tensor& m, float sx, float sy, float sz);
	tensor perspective(float fovInRadian, float aspect, float near, float far);
	tensor lookAt(const tensor& eye, const tensor& target, const tensor& up);
}

#endif