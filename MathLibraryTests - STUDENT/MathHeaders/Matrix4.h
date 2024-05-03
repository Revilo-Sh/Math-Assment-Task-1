#pragma once
#include <string>
#include "Vector4.h"

namespace MathClasses
{
	struct Matrix4
	{
		////////////////////////////
		// SetUp
		////////////////////////////

		union
		{
			struct
			{
				float m1, m2, m3, m4, m5, m6, m7, m8, m9 , m10 , m11, m12, m13, m14, m15, m16;
			};

			// 1-D array
			float v[16];

			// 2-D array
			float mm[4][4];

			Vector4 axis[4];
		};

		Matrix4() {
			m1 = m2 = m3 = m4 = m5 = m6 = m7 = m8 = m9 = m10 = m11 = m12 = m13 = m14 = m15 = m16 = 0.0f;
		}
		Matrix4(float _m1, float _m2, float _m3, float _m4, float _m5, float _m6, float _m7, float _m8, float _m9, float _m10, float _m11, float _m12, float _m13, float _m14, float _m15, float _m16) {
			m1 = _m1;
			m2 = _m2;
			m3 = _m3;
			m4 = _m4;
			m5 = _m5;
			m6 = _m6;
			m7 = _m7;
			m8 = _m8;
			m9 = _m9;
			m10 = _m10;
			m11 = _m11;
			m12 = _m12;
			m13 = _m13;
			m14 = _m14;
			m15 = _m15;
			m16 = _m16;
		}
		Matrix4(float numbers[]) {
			m1 = numbers[0];
			m2 = numbers[1];
			m3 = numbers[2];
			m4 = numbers[3];
			m5 = numbers[4];
			m6 = numbers[5];
			m7 = numbers[6];
			m8 = numbers[7];
			m9 = numbers[8];
			m10 = numbers[9];
			m11 = numbers[10];
			m12 = numbers[11];
			m13 = numbers[12];
			m14 = numbers[13];
			m15 = numbers[14];
			m16 = numbers[15];
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

		
		Matrix4 operator *(Matrix4 rhs) const
		{
			Matrix4 result;
			result.m1 = Vector4(m1, m5, m9 , m13).Dot(rhs.axis[0]);
			result.m2 = Vector4(m2, m6, m10, m14).Dot(rhs.axis[0]);
			result.m3 = Vector4(m3, m7, m11, m15).Dot(rhs.axis[0]);
			result.m4 = Vector4(m4, m8, m12, m16).Dot(rhs.axis[0]);

			result.m5 = Vector4(m1, m5, m9, m13).Dot(rhs.axis[1]);
			result.m6 = Vector4(m2, m6, m10, m14).Dot(rhs.axis[1]);
			result.m7 = Vector4(m3, m7, m11, m15).Dot(rhs.axis[1]);
			result.m8 = Vector4(m4, m8, m12, m16).Dot(rhs.axis[1]);

			result.m9 = Vector4(m1, m5, m9, m13).Dot(rhs.axis[2]);
			result.m10 = Vector4(m2, m6, m10, m14).Dot(rhs.axis[2]);
			result.m11 = Vector4(m3, m7, m11, m15).Dot(rhs.axis[2]);
			result.m12 = Vector4(m4, m8, m12, m16).Dot(rhs.axis[2]);

			result.m13 = Vector4(m1, m5, m9, m13).Dot(rhs.axis[3]);
			result.m14 = Vector4(m2, m6, m10, m14).Dot(rhs.axis[3]);
			result.m15 = Vector4(m3, m7, m11, m15).Dot(rhs.axis[3]);
			result.m16 = Vector4(m4, m8, m12, m16).Dot(rhs.axis[3]);

			return result;
		}

		Vector4 operator *(Vector4 rhs) const {
			return Vector4(
				Vector4(m1, m5, m9, m13).Dot(rhs),
				Vector4(m2, m6, m10, m14).Dot(rhs),
				Vector4(m3, m7, m11, m15).Dot(rhs),
				Vector4(m4, m8, m12, m16).Dot(rhs)
			);
		}

		operator float* () { return v;}
		operator const float* () { return v; }


		Matrix4 Transposed() const {
			return Matrix4(m1, m5, m9, m13, m2, m6, m10, m14, m3, m7, m11, m15, m4, m8, m12, m16);
		}

		std::string ToString() const {
			std::string str = std::to_string(v[0]);
			for (size_t i = 1; i < 9; ++i) {
				str += ", " + std::to_string(v[i]);
			}
			return str;
		}

		
		static Matrix4 MakeIdentity(){
			return Matrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
		}

		static Matrix4 MakeScale(float xScale, float yScale, float zScale) {
			return Matrix4(xScale, 0.0f, 0.0f, 0.0f,
				0.0f, yScale, 0.0f, 0.0f,
				0.0f, 0.0f, zScale, 0.0f,
				0.0f, 0.0f, 0.0f, 1);
		}

		static Matrix4 MakeScale(float xScale, float yScale) {
			return Matrix4(xScale, 0.0f, 0.0f, 0.0f,
				0.0f, yScale, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1);
		}

		static Matrix4 MakeScale(Vector3 other) {
			return MakeScale(other.x, other.y, other.z);
		}

		static Matrix4 MakeRotateX(float a) {
			return Matrix4(1, 0, 0, 0,
				0, cosf(a), -sinf(a), 0,
				0, sinf(a), cosf(a), 0,
				0, 0, 0, 1);
		}

		static Matrix4 MakeRotateY(float a) {
			return Matrix4(cosf(a), 0, sinf(a), 0,
				0, 1, 0, 0,
				-sinf(a), 0, cosf(a), 0,
				0, 0, 0, 1);
		}

		static Matrix4 MakeRotateZ(float a) {
			return Matrix4(cosf(a), sinf(a), 0, 0,
				-sinf(a), cosf(a), 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1);
		}

		static Matrix4 MakeTranslation(float x, float y, float z) {
			return Matrix4(
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				x, y, z, 1
			);
		}

		static Matrix4 MakeTranslation(Vector4 other) {
			return MakeTranslation(other.x, other.y, other.z);
		}

		static Matrix4 MakeTranslation(Vector3 other) {
			return MakeTranslation(other.x, other.y, other.z);
		}

		static Matrix4 MakeEuler(float pitch, float yaw, float roll) {
			Matrix4 x = MakeRotateX(pitch);
			Matrix4 y = MakeRotateY(yaw);
			Matrix4 z = MakeRotateZ(roll);

			return (z * y * x);
		}

		static Matrix4 MakeEuler(Vector3 other) {
			return MakeEuler(other.x, other.y, other.z);
		}

		bool operator == (const Matrix4& rhs) const {
			float m1Diff = (m1 - rhs.m1);
			float m2Diff = (m2 - rhs.m2);
			float m3Diff = (m3 - rhs.m3);
			float m4Diff = (m4 - rhs.m4);
			float m5Diff = (m5 - rhs.m5);
			float m6Diff = (m6 - rhs.m6);
			float m7Diff = (m7 - rhs.m7);
			float m8Diff = (m8 - rhs.m8);
			float m9Diff = (m9 - rhs.m9);

			float m10Diff = (m10 - rhs.m10);
			float m11Diff = (m11 - rhs.m11);
			float m12Diff = (m12 - rhs.m12);
			float m13Diff = (m13 - rhs.m13);
			float m14Diff = (m14 - rhs.m14);
			float m15Diff = (m15 - rhs.m15);
			float m16Diff = (m16 - rhs.m16);

			const float THRESHOLD = 0.00001f;
			return m1Diff < THRESHOLD && m2Diff < THRESHOLD && m3Diff < THRESHOLD && m4Diff < THRESHOLD && m5Diff
					< THRESHOLD && m6Diff < THRESHOLD && m7Diff < THRESHOLD && m8Diff < THRESHOLD && m9Diff
					< THRESHOLD&& m10Diff < THRESHOLD&& m11Diff < THRESHOLD&& m12Diff < THRESHOLD&& m13Diff
					< THRESHOLD&& m14Diff < THRESHOLD&& m15Diff < THRESHOLD&& m16Diff < THRESHOLD;
		}
	};
}