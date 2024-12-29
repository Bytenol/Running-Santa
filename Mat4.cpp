#include "Mat4.h"

using namespace mat4;


tensor mat4::create()
{
	return {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1,
	};
}

tensor mat4::translation(float tx, float ty, float tz)
{
	return {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		tx, ty, tz, 1,
	};
}

tensor mat4::xRotation(float angleInRadians)
{
	const float c = std::cos(angleInRadians);
	const float s = std::sin(angleInRadians);
	return {
		1, 0, 0, 0,
		0, c, s, 0,
		0, -s, c, 0,
		0, 0, 0, 1,
	};
}

tensor mat4::yRotation(float angleInRadians)
{
	const float c = std::cos(angleInRadians);
	const float s = std::sin(angleInRadians);
	return {
		c, 0, -s, 0,
		0, 1, 0, 0,
		s, 0, c, 0,
		0, 0, 0, 1,
	};
}

tensor mat4::zRotation(float angleInRadians)
{
	const float c = std::cos(angleInRadians);
	const float s = std::sin(angleInRadians);
	return {
		c, s, 0, 0,
		-s, c, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1,
	};
}

tensor mat4::scaling(float sx, float sy, float sz)
{
	return {
		sx, 0, 0, 0,
		0, sy, 0, 0,
		0, 0, sz, 0,
		0, 0, 0, 1,
	};
}

tensor mat4::translate(const tensor& m, float tx, float ty, float tz)
{
	return multiply(m, translation(tx, ty, tz));
}

tensor mat4::multiply(const tensor& a, const tensor& b)
{
	const float b00 = b[0 * 4 + 0];
	const float b01 = b[0 * 4 + 1];
	const float b02 = b[0 * 4 + 2];
	const float b03 = b[0 * 4 + 3];
	const float b10 = b[1 * 4 + 0];
	const float b11 = b[1 * 4 + 1];
	const float b12 = b[1 * 4 + 2];
	const float b13 = b[1 * 4 + 3];
	const float b20 = b[2 * 4 + 0];
	const float b21 = b[2 * 4 + 1];
	const float b22 = b[2 * 4 + 2];
	const float b23 = b[2 * 4 + 3];
	const float b30 = b[3 * 4 + 0];
	const float b31 = b[3 * 4 + 1];
	const float b32 = b[3 * 4 + 2];
	const float b33 = b[3 * 4 + 3];
	const float a00 = a[0 * 4 + 0];
	const float a01 = a[0 * 4 + 1];
	const float a02 = a[0 * 4 + 2];
	const float a03 = a[0 * 4 + 3];
	const float a10 = a[1 * 4 + 0];
	const float a11 = a[1 * 4 + 1];
	const float a12 = a[1 * 4 + 2];
	const float a13 = a[1 * 4 + 3];
	const float a20 = a[2 * 4 + 0];
	const float a21 = a[2 * 4 + 1];
	const float a22 = a[2 * 4 + 2];
	const float a23 = a[2 * 4 + 3];
	const float a30 = a[3 * 4 + 0];
	const float a31 = a[3 * 4 + 1];
	const float a32 = a[3 * 4 + 2];
	const float a33 = a[3 * 4 + 3];
	return {
		b00* a00 + b01 * a10 + b02 * a20 + b03 * a30,
		b00* a01 + b01 * a11 + b02 * a21 + b03 * a31,
		b00* a02 + b01 * a12 + b02 * a22 + b03 * a32,
		b00* a03 + b01 * a13 + b02 * a23 + b03 * a33,
		b10* a00 + b11 * a10 + b12 * a20 + b13 * a30,
		b10* a01 + b11 * a11 + b12 * a21 + b13 * a31,
		b10* a02 + b11 * a12 + b12 * a22 + b13 * a32,
		b10* a03 + b11 * a13 + b12 * a23 + b13 * a33,
		b20* a00 + b21 * a10 + b22 * a20 + b23 * a30,
		b20* a01 + b21 * a11 + b22 * a21 + b23 * a31,
		b20* a02 + b21 * a12 + b22 * a22 + b23 * a32,
		b20* a03 + b21 * a13 + b22 * a23 + b23 * a33,
		b30* a00 + b31 * a10 + b32 * a20 + b33 * a30,
		b30* a01 + b31 * a11 + b32 * a21 + b33 * a31,
		b30* a02 + b31 * a12 + b32 * a22 + b33 * a32,
		b30* a03 + b31 * a13 + b32 * a23 + b33 * a33,
	};
}

tensor mat4::xRotate(const tensor& m, float angleInRadians)
{
	return multiply(m, xRotation(angleInRadians));
}

tensor mat4::yRotate(const tensor& m, float angleInRadians)
{
	return multiply(m, yRotation(angleInRadians));
}

tensor mat4::zRotate(const tensor& m, float angleInRadians)
{
	return multiply(m, zRotation(angleInRadians));
}

tensor mat4::scale(const tensor& m, float sx, float sy, float sz)
{
	return multiply(m, scaling(sx, sy, sz));
}

tensor mat4::perspective(float fovInRadian, float aspect, float near, float far)
{
	const float f = std::tan(3.14159f * 0.5f - 0.5f * fovInRadian);
	const float rangeInv = 1.0 / (near - far);
	return {
		f / aspect, 0, 0, 0,
		0, f, 0, 0,
		0, 0, (near + far) * rangeInv, -1,
		0, 0, near * far * rangeInv * 2, 0
	};
}

tensor mat4::lookAt(const tensor& eye, const tensor& target, const tensor& up)
{
	auto normalize = [](const tensor& v) -> tensor {
		const float length = std::sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
		if (length > 0)
			return { v[0] / length, v[1] / length, v[2] / length };
		return { 0, 0, 0 };
	};

	auto cross = [](const tensor& a, const tensor& b) -> tensor {
		return {
			a[1] * b[2] - a[2] * b[1],
			a[2] * b[0] - a[0] * b[2],
			a[0] * b[1] - a[1] * b[0]
		};
	};

	auto dot = [](const tensor& a, const tensor& b) -> float {
		return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
	};

	const tensor zAxis = normalize({ eye[0] - target[0], eye[1] - target[1], eye[2] - target[2] });
	const tensor xAxis = normalize(cross(up, zAxis));
	const tensor yAxis = normalize(cross(zAxis, xAxis));
	return {
		xAxis[0], yAxis[0], zAxis[0], 0,
		xAxis[1], yAxis[1], zAxis[1], 0,
		xAxis[2], yAxis[2], zAxis[2], 0,
		-dot(xAxis, eye), -dot(yAxis, eye), -dot(zAxis, eye), 1
	};
}
