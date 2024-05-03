#pragma once
#include <string>

namespace MathClasses
{
    struct Vector4
    {
        union {
            struct { float x, y, z, w; };
            struct { float r, g, b, w; };
            float data[3];
        };

        Vector4() : x{ 0 }, y{ 0 }, z{ 0 } , w{ 0 }
        {}

        Vector4(float  _x, float _y, float _z, float _w) {
            x = _x;
            y = _y;
            z = _z;
            w = _w;
        }

        float& operator [](int dim) {
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

        Vector4 operator + (const Vector4& rhs) const {
            Vector4 sum;
            sum.x = x + rhs.x;
            sum.y = y + rhs.y;
            sum.z = z + rhs.z;
            sum.w = w + rhs.w;


            return sum;
        }

        Vector4 operator - (const Vector4& rhs) const {
            Vector4 sum;
            sum.x = x - rhs.x;
            sum.y = y - rhs.y;
            sum.z = z - rhs.z;
            sum.w = w - rhs.w;

            return sum;
        }

        Vector4 operator * (float num) const {
            Vector4 sum;
            sum.x = x * num;
            sum.y = y * num;
            sum.z = z * num;
            sum.w = w * num;

            return sum;
        }

        Vector4 operator / (float num) const {
            Vector4 sum;
            sum.x = x / num;
            sum.y = y / num;
            sum.z = z / num;
            sum.w = w / num;

            return sum;
        }

        bool operator == (const Vector4& rhs) const {
            float xDist = fabsf(x - rhs.x);
            float yDist = fabsf(y - rhs.y);
            float zDist = fabsf(z - rhs.z);
            float wDist = fabsf(w - rhs.w);

            const float THRESHOLD = 0.00001f;
            return xDist < THRESHOLD && yDist < THRESHOLD && zDist < THRESHOLD && wDist < THRESHOLD;
        }

        bool operator != (const Vector4& rhs) const {
            return !(*this == rhs);
        }

        std::string ToString() const {
            return std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + std::to_string(w) + ", ";
        }


        //----------------------\\
        //Magnitude
        //-----------------------

        float Magnitude() const {
            return sqrtf(x * x + y * y + z * z + w * w);
        }

        float MagnitudeSqr() const {
            return x * x + y * y + z * z + w * w;
        }

        float Distance(const Vector4& other) const {
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

                if (w != 0)
                    w /= m;
            }
            else {
                x = y = z = w = 0;
            }

        }

        Vector4 Normalised() const {
            Vector4 copy = *this;
            copy.Normalise();

            return copy;
        }


        //----------------------\\
        //Dot Cross
        //-----------------------

        float Dot(const Vector4& other) {
            return w * other.w + x * other.x + y * other.y + z * other.z;
        }

        Vector4 Vector4::Cross(const Vector4& other)
        {
            Vector4 crossdata;
            crossdata.x = (y * other.z) - (z * other.y);
            crossdata.y = (z * other.x) - (x * other.z);
            crossdata.z = (x * other.y) - (y * other.x);
            crossdata.w = 0;

            return crossdata;

        }
    };

}