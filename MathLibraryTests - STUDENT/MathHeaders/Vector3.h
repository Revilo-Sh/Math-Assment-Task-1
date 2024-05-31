#pragma once
#include <string>
#include "Utils.h"

namespace MathClasses
{
    struct Vector3
    {
        union {
            struct { float x, y, z; };
            struct { float r, g, b; };
            float data[3];
        };

        Vector3() : x{ 0 }, y{ 0 }, z{ 0 }
        {}

        Vector3(float  _x, float _y, float _z) {
            x = _x;
            y = _y;
            z = _z;
        }

        float & operator [](int dim) {
            return data[dim];
        }

        const float& operator [](int dim) const {
            return data[dim];
        }

        operator float* () { return data; }

        operator const float* () const { return data; };


        //----------------------\\
        //Operators
        //-----------------------
        
        Vector3 operator + (const Vector3& rhs) const {
            Vector3 sum;
            sum.x = x + rhs.x;
            sum.y = y + rhs.y;
            sum.z = z + rhs.z;

            return sum;
        }

        Vector3 operator - (const Vector3& rhs) const {
            Vector3 sum;
            sum.x = x - rhs.x;
            sum.y = y - rhs.y;
            sum.z = z - rhs.z;

            return sum;
        }

        Vector3 operator * (const float num) {
            Vector3 sum;
            sum.x = x * num;
            sum.y = y * num;
            sum.z = z * num;

            return sum;
        }

        Vector3 operator / (const float num) {
            Vector3 sum;
            sum.x = x / num;
            sum.y = y / num;
            sum.z = z / num;

            return sum;
        }

        bool operator == (const Vector3& rhs) const {
            float xDist = fabsf(x - rhs.x);
            float yDist = fabsf(y - rhs.y);
            float zDist = fabsf(z - rhs.z);
           
            const float THRESHOLD = 0.00001f;
            return xDist < THRESHOLD && yDist < THRESHOLD && zDist < THRESHOLD;
        }

        Vector3 operator += (const Vector3 num){
            x = this->x + num.x;
            y = this->y + num.y;
            z = this->z + num.z;

            return *this;

        }

        Vector3 operator *= (const float rhs) {
            x = x * rhs; 
            y = y * rhs;
            z = z * rhs;

            return *this;
        }

        Vector3 operator *= (const Vector3 rhs) {
            x = x * rhs.x;
            y = y * rhs.y;
            z = z * rhs.z;

            return *this;
        }

        bool operator != (const Vector3& rhs) const {
            return !(*this == rhs);
        }

        std::string ToString() const {
            return std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z);
        }
        

        //----------------------\\
        //Magnitude
        //-----------------------

        float Magnitude() const {
            return sqrtf(x * x + y * y + z * z);
        }

        float MagnitudeSqr() const {
            return x * x + y * y + z * z;
        }

        float Distance(const Vector3& other) const {
            return (*this - other).Magnitude();
        }
        
        void Normalise() {
            float m = Magnitude();
            if (m != 0) {
                if (x != 0)
                    x /= m;

                if (y != 0)
                    y /= m;

                if (z != 0)
                    z /= m;
            }
            else {
                x = y = z = 0;
            }

        }

        Vector3 Normalised() const {
            Vector3 copy = *this;
            copy.Normalise();

            return copy;
        }


        //----------------------\\
        //Dot Cross
        //-----------------------

        float Dot(const Vector3& other) {
            return x * other.x + y * other.y + z * other.z;
        }

        Vector3 Vector3::Cross(const Vector3& other)
        {
            Vector3 crossdata;
            crossdata.x = (y * other.z) - (z * other.y);
            crossdata.y = (z * other.x) - (x * other.z);
            crossdata.z = (x * other.y) - (y * other.x);

            return crossdata;

        }
	};

}