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
}