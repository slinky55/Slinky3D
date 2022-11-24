#pragma once

#include "Slinky/Math/Vector3.hpp"

namespace Slinky
{
    struct Particle
    {
        Math::Vector3 position;
        Math::Vector3 velocity;
        Math::Vector3 acceleration;

        Math::Vector3 forces;

        float invMass {0};
        float restitution {0};
        float damping {0};

        Particle(const Math::Vector3& _pos,
                 float _mass,
                 float _restitution,
                 float _damping);

        void Integrate(float _dt);

        void ApplyForce(const Math::Vector3& _force);
        void ClearForces();
    };
}