#pragma once
#include <string>
#include "Vector3.h"

namespace MathClasses
{
	struct Matrix3
	{
		////////////////////////////
		// SetUp
		////////////////////////////

		union
		{
			struct
			{
				float m1, m2, m3, m4, m5, m6, m7, m8, m9;
			};

			// 1-D array
			float v[9];

			// 2-D array
			float mm[3][3];

			Vector3 axis[3];
		};

		Matrix3() {
			m1 = m2 = m3 = m4 = m5 = m6 = m7 = m8 = m9 = 0.0f;
		}
		Matrix3(float _m1, float _m2, float _m3, float _m4, float _m5, float _m6, float _m7, float _m8, float _m9) {
			m1 = _m1;
			m2 = _m2;
			m3 = _m3;
			m4 = _m4;
			m5 = _m5;
			m6 = _m6;
			m7 = _m7;
			m8 = _m8;
			m9 = _m9;
		}
		Matrix3(float numbers[]) {
			m1 = numbers[0];
			m2 = numbers[1];
			m3 = numbers[2];
			m4 = numbers[3];
			m5 = numbers[4];
			m6 = numbers[5];
			m7 = numbers[6];
			m8 = numbers[7];
			m9 = numbers[8];
		}

		////////////////////////////
		// Subscript Operator
		////////////////////////////

		float& operator [](int dim) {
			return v[dim];
		}

		const float& operator [](int dim) const {
			return v[dim];
		}

		////////////////////////////
		// Matrix Multiplication
		////////////////////////////


		Matrix3 operator *(Matrix3 rhs) const
		{
			Matrix3 result;

			result.m1 = Vector3(m1, m4, m7).Dot(rhs.axis[0]);
			result.m2 = Vector3(m2, m5, m8).Dot(rhs.axis[0]);
			result.m3 = Vector3(m3, m6, m9).Dot(rhs.axis[0]);

			result.m4 = Vector3(m1, m4, m7).Dot(rhs.axis[1]);
			result.m5 = Vector3(m2, m5, m8).Dot(rhs.axis[1]);
			result.m6 = Vector3(m3, m6, m9).Dot(rhs.axis[1]);

			result.m7 = Vector3(m1, m4, m7).Dot(rhs.axis[2]);
			result.m8 = Vector3(m2, m5, m8).Dot(rhs.axis[2]);
			result.m9 = Vector3(m3, m6, m9).Dot(rhs.axis[2]);

			return result;
		}

		Vector3 operator *(Vector3 rhs) const {
			return Vector3(
				Vector3(m1, m4, m7).Dot(rhs),
				Vector3(m2, m5, m8).Dot(rhs),
				Vector3(m3, m6, m9).Dot(rhs)
			);
		}

		operator float* () { return v; }
		operator const float* () { return v; }


		Matrix3 Transposed() const { 
			return Matrix3(m1, m4, m7, m2, m5, m8, m3, m6, m9);
		}

		std::string ToString() const {
			std::string str = std::to_string(v[0]);
			for (size_t i = 1; i < 9; ++i) {
				str += ", " + std::to_string(v[i]);
			}
			return str;
		}


		static Matrix3 MakeIdentity() {
			return Matrix3(1, 0, 0, 0, 1, 0, 0, 0, 1);
		}

		static Matrix3 MakeScale(float xScale, float yScale, float zScale) {
			return Matrix3(xScale, 0.0f, 0.0f,
				0.0f, yScale, 0.0f,
				0.0f, 0.0f, zScale);
		}

		static Matrix3 MakeScale(float xScale, float yScale) {
			return Matrix3(xScale, 0.0f, 0.0f,
				0.0f, yScale, 0.0f, 
				0.0f, 0.0f, 1.0f);
		}

		static Matrix3 MakeScale(Vector3 other) {
			return MakeScale(other.x, other.y, other.z);
		}

		static Matrix3 MakeRotateX(float a) {
			return Matrix3(1, 0, 0,
				0, cosf(a), -sinf(a),
				0, sinf(a), cosf(a));
		}

		static Matrix3 MakeRotateY(float a) {
			return Matrix3(cosf(a), 0, sinf(a),
				0, 1, 0,
				-sinf(a), 0, cosf(a));
		}

		static Matrix3 MakeRotateZ(float a) {
			return Matrix3(cosf(a), sinf(a), 0,
				-sinf(a), cosf(a), 0,
				0, 0, 1);
		}

		static Matrix3 MakeTranslation(float x, float y, float z) {
			return Matrix3(
				1, 0, 0,
				0, 1, 0,
				x, y, z
			);
		}

	

		static Matrix3 MakeTranslation(Vector3 other) {
			return MakeTranslation(other.x, other.y, other.z);
		}

		static Matrix3 MakeEuler(float pitch, float yaw, float roll) {
			Matrix3 x = MakeRotateX(pitch);
			Matrix3 y = MakeRotateY(yaw);
			Matrix3 z = MakeRotateZ(roll);

			return (z * y * x);
		}

		static Matrix3 MakeEuler(Vector3 other) {
			return MakeEuler(other.x, other.y, other.z);
		}



		///missing operator == overload


		bool operator == (const Matrix3& rhs) const {
			float m1Diff = (m1 - rhs.m1);
			float m2Diff = (m2 - rhs.m2);
			float m3Diff = (m3 - rhs.m3);
			float m4Diff = (m4 - rhs.m4);
			float m5Diff = (m5 - rhs.m5);
			float m6Diff = (m6 - rhs.m6);
			float m7Diff = (m7 - rhs.m7);
			float m8Diff = (m8 - rhs.m8);
			float m9Diff = (m9 - rhs.m9);
		
			const float THRESHOLD = 0.00001f;
			return m1Diff < THRESHOLD && m2Diff < THRESHOLD && m3Diff < THRESHOLD && m4Diff < THRESHOLD && m5Diff < THRESHOLD && m6Diff < THRESHOLD && m7Diff < THRESHOLD && m8Diff < THRESHOLD && m9Diff < THRESHOLD;
		}
	};
}