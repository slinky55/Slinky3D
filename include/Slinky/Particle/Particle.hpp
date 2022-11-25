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

#include "Slinky/Math/Vector3.hpp"

namespace Slinky
{
    struct Particle
    {
        // Transform
        Math::Vector3 position;
        Math::Vector3 velocity;
        Math::Vector3 acceleration;

        // Force accumulator
        Math::Vector3 forces;

        // Radius for collisions
        float radius;

        // Mass in kg
        float mass {0};
        float invMass {0};

        // Coefficient of restitution
        float restitution {0};

        // Damping coefficient
        float damping {0};

        Particle(const Math::Vector3& _pos,
                 float _radius,
                 float _mass,
                 float _restitution,
                 float _damping);

        void Integrate(float _dt);

        void ApplyForce(const Math::Vector3& _force);
        void ClearForces();
    };
}