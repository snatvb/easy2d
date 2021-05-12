#pragma once
#include <cmath>

namespace easy2d
{
    template <class T>
    class vec2d
    {
    public:
        T x;
        T y;

        vec2d() : x(0), y(0) {}
        vec2d(T x, T y) : x(x), y(y) {}
        vec2d(const vec2d &v) : x(v.x), y(v.y) {}

        vec2d &operator=(const vec2d &v)
        {
            x = v.x;
            y = v.y;
            return *this;
        }

        vec2d operator+(vec2d &v)
        {
            return vec2d(x + v.x, y + v.y);
        }
        vec2d operator-(vec2d &v)
        {
            return vec2d(x - v.x, y - v.y);
        }

        vec2d &operator+=(vec2d &v)
        {
            x += v.x;
            y += v.y;
            return *this;
        }

        vec2d &operator-=(vec2d &v)
        {
            x -= v.x;
            y -= v.y;
            return *this;
        }

        vec2d operator+(double s)
        {
            return vec2d(x + s, y + s);
        }
        vec2d operator-(double s)
        {
            return vec2d(x - s, y - s);
        }
        vec2d operator*(double s)
        {
            return vec2d(x * s, y * s);
        }
        vec2d operator/(double s)
        {
            return vec2d(x / s, y / s);
        }

        vec2d &operator+=(double s)
        {
            x += s;
            y += s;
            return *this;
        }

        vec2d &operator-=(double s)
        {
            x -= s;
            y -= s;
            return *this;
        }

        vec2d &operator*=(double s)
        {
            x *= s;
            y *= s;
            return *this;
        }

        vec2d &operator/=(double s)
        {
            x /= s;
            y /= s;
            return *this;
        }

        void set(T x, T y)
        {
            this->x = x;
            this->y = y;
        }

        void rotate(double deg)
        {
            double theta = deg / 180.0 * M_PI;
            double c = cos(theta);
            double s = sin(theta);
            double tx = x * c - y * s;
            double ty = x * s + y * c;
            x = tx;
            y = ty;
        }

        vec2d &normalize()
        {
            if (length() == 0)
                return *this;
            *this *= (1.0 / length());
            return *this;
        }

        float dist(vec2d v) const
        {
            vec2d d(v.x - x, v.y - y);
            return d.length();
        }

        float length() const
        {
            return std::sqrt(x * x + y * y);
        }

        void truncate(double length)
        {
            double angle = atan2f(y, x);
            x = length * cos(angle);
            y = length * sin(angle);
        }

        vec2d ortho() const
        {
            return vec2d(y, -x);
        }

        static float dot(vec2d v1, vec2d v2)
        {
            return v1.x * v2.x + v1.y * v2.y;
        }

        static float cross(vec2d v1, vec2d v2)
        {
            return (v1.x * v2.y) - (v1.y * v2.x);
        }
    };

    typedef vec2d<float> vec2df;
    typedef vec2d<double> vec2dd;
    typedef vec2d<int> vec2di;
} // -- easy2d