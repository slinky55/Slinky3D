#include "Slinky/Particle/Particle.hpp"

namespace Slinky
{
    Particle::Particle(const Math::Vector3 &_pos,
                       float _mass,
                       float _restitution,
                       float _damping)
                       :
                       position{_pos},
                       invMass{1/_mass},
                       restitution{_restitution},
                       damping{_damping}
    {}

    void Particle::Integrate(float _dt)
    {
        if(invMass <= 0.0f ||
           _dt <= 0.0f)
            return;

        position += velocity * _dt;

        Math::Vector3 resultingAcc = acceleration;
        resultingAcc += forces * invMass;

        velocity += resultingAcc * _dt;
        velocity *= powf(damping, _dt);
    }

    void Particle::ApplyForce(const Math::Vector3 &_force)
    {
        forces += _force;
    }

    void Particle::ClearForces()
    {
        forces = Math::Vector3{0.0f};
    }
}