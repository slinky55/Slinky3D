#include "Slinky/Dynamics/RigidBody.hpp"

namespace Slinky
{
    RigidBody::RigidBody(const Math::Vector3& _position,
                         const Math::Vector3& _size,
                         float _mass,
                         float _restitution,
                         float _damping)
                         :
                         m_position{_position},
                         m_size{_size},
                         m_mass{_mass},
                         m_invMass{_mass > 0 ? 1.0f / _mass : 0},
                         m_restitution{_restitution},
                         m_damping{_damping},
                         m_collider{ {_position}, {_size / 2.f}}
    {}

    void RigidBody::Integrate(float _dt)
    {
        if (m_mass == 0) return;

        m_position += m_velocity * _dt;
        m_collider.center = m_position;

        Math::Vector3 resultingAcc { m_acceleration + m_forces * m_invMass };
        m_velocity += resultingAcc * _dt;
        m_velocity *= powf(m_damping, _dt);

        ClearForces();
    }
    void RigidBody::ApplyForce(const Math::Vector3& _force)
    {
        m_forces += _force;
    }
    void RigidBody::ClearForces() { m_forces = Math::Vector3{0.f, 0.f, 0.f}; }

    Math::Vector3& RigidBody::Position() { return m_position; }
    Math::Vector3& RigidBody::Velocity() { return m_velocity; }
    Math::Vector3& RigidBody::Acceleration() { return m_acceleration; }
    Math::Vector3& RigidBody::Size() { return m_size; }
    float& RigidBody::Mass() { return m_mass; }
    float& RigidBody::InvMass() { return m_invMass; }
    float& RigidBody::Restitution() { return m_restitution; }
    float& RigidBody::Damping() { return m_damping; }

    const Collision::AABB& RigidBody::GetAABB() const { return m_collider; }
}