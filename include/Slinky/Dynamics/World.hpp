#pragma once

#include <vector>

#include "Slinky/Dynamics/RigidBody.hpp"
#include "Slinky/Math/Vector3.hpp"

namespace Slinky
{
    class World
    {
    public:
        World( const Math::Vector3& _gravity = { 0.0f, -9.81f, 0.0f } );
        ~World();

        void Step(float _dt);

        const std::vector<std::shared_ptr<RigidBody>>& Bodies() const;
    private:
        std::vector<std::shared_ptr<RigidBody>> m_bodies;

        Math::Vector3 m_gravity;
    };
}