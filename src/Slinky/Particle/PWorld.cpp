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

#include "Slinky/Particle/PWorld.hpp"

namespace Slinky
{
    PWorld::PWorld(const Math::Vector3& _gravity)
        : m_gravity(_gravity)
    {
    }

    const Particle* PWorld::CreateParticle(const Particle& _particle)
    {
        m_particles.push_back(std::make_shared<Particle>(_particle));
        return m_particles.back().get();
    }

    void PWorld::DestroyParticle(const Particle* _particle)
    {
        for (auto it = m_particles.begin(); it != m_particles.end(); ++it)
        {
            if (it->get() == _particle)
            {
                m_particles.erase(it);
                break;
            }
        }
    }

    void PWorld::Step(float _dt) const
    {
        for (auto const& particle : m_particles)
        {
            particle->ApplyForce(m_gravity * particle->mass);
            particle->Integrate(_dt);
        }
    }
}