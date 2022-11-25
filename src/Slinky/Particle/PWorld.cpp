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
    PWorld::PWorld(const Math::Vector3& _gravity,
                   uint32_t _itrs)
        :
        m_gravity{_gravity},
        m_iterations{_itrs}
    {
    }

    void PWorld::Step(float _dt)
    {
        /*
         * Clear particle forces
         */
        PReg* reg = particles;
        while (reg)
        {
            reg->particle->ClearForces();
            reg = reg->next;
        }

        /*
         * Apply gravity
         */
        reg = particles;
        while (reg)
        {
            reg->particle->ApplyForce(m_gravity * reg->particle->mass);
            reg = reg->next;
        }

        /*
         * Integrate particles
         */
        reg = particles;
        while (reg)
        {
            reg->particle->Integrate(_dt);
            reg = reg->next;
        }

        uint32_t contactsUsed { GenerateContacts() };
        if (m_iterations == 0) ResolveContacts(contacts, contactsUsed, contactsUsed * 2, _dt);
        else ResolveContacts(contacts, contactsUsed, m_iterations, _dt);
    }

    uint32_t PWorld::GenerateContacts()
    {
        uint32_t limit { MAX_CONTACTS };
        PContact* next { contacts };

        PContactGeneratorReg* reg { contactGenerators };
        while (reg)
        {
            uint32_t used { reg->gen->AddContact(next, limit) };
            limit -= used;

            next += used;

            if (limit <= 0) break;

            reg = reg->next;
        }

        // Contacts used
        return MAX_CONTACTS - limit;
    }
}