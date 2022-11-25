#pragma once

#include "Slinky/Math/Vector3.hpp"
#include "Slinky/Collision/AABB.h"

namespace Slinky
{
    class RigidBody
    {
    public:
        RigidBody(const Math::Vector3& _position,
                  const Math::Vector3& _size,
                  float _mass,
                  float _restitution,
                  float _damping);

        void Integrate(float _dt);

        void ApplyForce(const Math::Vector3& _force);
        void ClearForces();

        [[nodiscard]] Math::Vector3& Position();
        [[nodiscard]] Math::Vector3& Velocity();
        [[nodiscard]] Math::Vector3& Acceleration();
        [[nodiscard]] Math::Vector3& Size();
        [[nodiscard]] float& Mass();
        [[nodiscard]] float& InvMass();
        [[nodiscard]] float& Restitution();
        [[nodiscard]] float& Damping();

        [[nodiscard]] const Collision::AABB& GetAABB() const;

    private:
        Math::Vector3 m_position;
        Math::Vector3 m_velocity;
        Math::Vector3 m_acceleration;
        Math::Vector3 m_size;

        Math::Vector3 m_forces;

        float m_mass;
        float m_invMass;
        float m_restitution;
        float m_damping;

        Collision::AABB m_collider;
    };
}