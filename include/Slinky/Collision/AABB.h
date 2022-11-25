#pragma once

#include "Slinky/Math/Vector3.hpp"

namespace Slinky::Collision
{
    struct AABB
    {
        Math::Vector3 center;
        Math::Vector3 halfSize;

        AABB(const Math::Vector3 &_center,
             const Math::Vector3 &_halfSize)
             :
             center{_center},
             halfSize{_halfSize}
        {}

        [[nodiscard]] bool Contains(const Math::Vector3 &_point) const
        {
            return
                    _point.x >= center.x - halfSize.x &&
                    _point.x <= center.x + halfSize.x &&
                    _point.y >= center.y - halfSize.y &&
                    _point.y <= center.y + halfSize.y &&
                    _point.z >= center.z - halfSize.z &&
                    _point.z <= center.z + halfSize.z;
        }
        [[nodiscard]] bool Intersects(const AABB &_other) const
        {
            return
                    center.x - halfSize.x <= _other.center.x + _other.halfSize.x &&
                    center.x + halfSize.x >= _other.center.x - _other.halfSize.x &&
                    center.y - halfSize.y <= _other.center.y + _other.halfSize.y &&
                    center.y + halfSize.y >= _other.center.y - _other.halfSize.y &&
                    center.z - halfSize.z <= _other.center.z + _other.halfSize.z &&
                    center.z + halfSize.z >= _other.center.z - _other.halfSize.z;
        }
    };
}
