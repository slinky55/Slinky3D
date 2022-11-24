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


#include "Slinky/Particle/Particle.hpp"

namespace Slinky
{
    Particle::Particle(const Math::Vector3 &_pos,
                       float _mass,
                       float _restitution,
                       float _damping)
                       :
                       position{_pos},
                       mass{_mass},
                       invMass{ (_mass > 0) ? 1 / _mass : 0 },
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

        ClearForces();
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