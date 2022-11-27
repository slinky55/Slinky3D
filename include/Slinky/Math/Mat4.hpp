#pragma once

#include <array>

#include "Slinky/Math/Vector3.hpp"

namespace Slinky::Math
{
    struct Mat4
    {
        std::array<float, 16> data;

        [[nodiscard]] constexpr Math::Vector3 operator*(const Math::Vector3& _vec) const noexcept;
    };
}