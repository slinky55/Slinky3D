/*
    MIT License

    Copyright (c) 2022 slinky55

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#pragma once

#include <cmath>

namespace Slinky::Math
{
    struct Vector3 {
        float x;
        float y;
        float z;

        constexpr Vector3() noexcept
                :
                x{0.0f},
                y{0.0f},
                z{0.0f} {}

        constexpr Vector3(float _x,
                          float _y,
                          float _z) noexcept
                :
                x{_x},
                y{_y},
                z{_z} {}

        explicit constexpr Vector3(float _scalar) noexcept
                :
                x{_scalar},
                y{_scalar},
                z{_scalar} {}

        [[nodiscard]] constexpr Vector3 operator+(const Vector3 &_rhs) const noexcept {
            return {
                    x + _rhs.x,
                    y + _rhs.y,
                    z + _rhs.z
            };
        }
        [[nodiscard]] constexpr Vector3 operator-(const Vector3 &_rhs) const noexcept {
            return {
                    x - _rhs.x,
                    y - _rhs.y,
                    z - _rhs.z
            };
        }
        [[nodiscard]] constexpr Vector3 operator*(float _scalar) const noexcept {
            return {
                    x * _scalar,
                    y * _scalar,
                    z * _scalar
            };
        }
        [[nodiscard]] constexpr Vector3 operator/(float _scalar) const noexcept {
            return {
                    x / _scalar,
                    y / _scalar,
                    z / _scalar
            };
        }

        // Dot product
        [[nodiscard]] constexpr float operator*(const Vector3 &_rhs) const noexcept {
            return x * _rhs.x + y * _rhs.y + z * _rhs.z;
        }

        constexpr void operator+=(const Vector3 &_rhs) noexcept {
            x += _rhs.x;
            y += _rhs.y;
            z += _rhs.z;
        }
        constexpr void operator-=(const Vector3 &_rhs) noexcept {
            x -= _rhs.x;
            y -= _rhs.y;
            z -= _rhs.z;
        }
        constexpr void operator*=(float _scalar) noexcept {
            x *= _scalar;
            y *= _scalar;
            z *= _scalar;
        }
        constexpr void operator/=(float _scalar) noexcept {
            x /= _scalar;
            y /= _scalar;
            z /= _scalar;
        }

        [[nodiscard]] constexpr float Magnitude() const noexcept {
            return std::sqrtf(x * x + y * y + z * z);
        }
        [[nodiscard]] constexpr float MagnitudeSq() const noexcept
        {
            return x * x + y * y + z * z;
        }
        [[nodiscard]] constexpr Vector3 Normalized() const noexcept
        {
            return *this / Magnitude();
        }
    };

    inline float Distance(const Vector3 &_lhs, const Vector3 &_rhs)
    {
        return (_lhs - _rhs).Magnitude();
    }
}