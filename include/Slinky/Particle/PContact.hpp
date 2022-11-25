#pragma once

#include <array>

#include "Slinky/Math/Vector3.hpp"
#include "Slinky/Particle/Particle.hpp"

namespace Slinky {

    struct PContact
    {
        std::array<Particle*, 2> particle;

        float restitution;

        Math::Vector3 normal;

        float intersection;

        float SeparatingVelocity() const
        {
            return (particle[1]
                   ?
                   particle[0]->velocity - particle[1]->velocity
                   :
                   particle[0]->velocity) * normal;
        }
    };

    inline void ResolveVelocity(const PContact* _c, float _dt)
    {
        float separatingVelocity { _c->SeparatingVelocity() };

        if (separatingVelocity > 0) return;

        float newSepVelocity { -separatingVelocity * _c->restitution };

        Math::Vector3 velocityFromAcc {
            _c->particle[1]
            ?
            _c->particle[0]->acceleration - _c->particle[1]->acceleration
            :
            _c->particle[0]->acceleration
        };

        float sepVelocityFromAcc { velocityFromAcc * _c->normal * _dt };

        if (sepVelocityFromAcc < 0)
        {
            newSepVelocity += _c->restitution * sepVelocityFromAcc;

            if (newSepVelocity < 0) newSepVelocity = 0;
        }

        float deltaVelocity { newSepVelocity - separatingVelocity };

        float totalInverseMass {
            _c->particle[1]
            ?
            _c->particle[0]->invMass + _c->particle[1]->invMass
            :
            _c->particle[0]->invMass
        };

        if (_c->particle[1]) totalInverseMass += _c->particle[1]->invMass;

        if (totalInverseMass <= 0) return;

        float impulse { deltaVelocity / totalInverseMass };

        Math::Vector3 impulsePerIMass { _c->normal * impulse };

        _c->particle[0]->velocity += impulsePerIMass * _c->particle[0]->invMass;

        if (_c->particle[1])
            _c->particle[1]->velocity -= impulsePerIMass * _c->particle[1]->invMass;
    }
    inline void ResolveIntersection(const PContact* _c, float _dt)
    {
        if (_c->intersection <= 0) return;

        float totalInvMass {
            _c->particle[1]
            ?
            _c->particle[0]->invMass + _c->particle[1]->invMass
            :
            _c->particle[0]->invMass
        };

        if (totalInvMass <= 0) return;

        Math::Vector3 movePerInvMass { _c->normal * (-_c->intersection / totalInvMass) };

        _c->particle[0]->position += movePerInvMass * _c->particle[0]->invMass;

        if (_c->particle[1])
            _c->particle[1]->position += movePerInvMass * _c->particle[1]->invMass;
    }

    inline void ResolveContact(const PContact* _c, float _dt)
    {
        ResolveVelocity(_c, _dt);
        ResolveIntersection(_c, _dt);
    }

    inline void ResolveContacts(PContact* _contacts,
                                uint32_t _numContacts,
                                uint32_t _iterations,
                                float _dt)
    {
        for (uint32_t itr { 0 }; itr < _iterations; itr++)
        {
            float max { 0 };
            std::size_t maxIndex { _numContacts };
            for (uint32_t i {0}; i < _numContacts; i++)
            {
                float vel { _contacts[i].SeparatingVelocity() };
                if (vel < max)
                {
                    max = vel;
                    maxIndex = i;
                }
            }

            ResolveContact(&_contacts[maxIndex], _dt);
        }
    }

    class PContactGenerator
    {
    public:
        virtual uint32_t AddContact(PContact* contacts,
                                    uint32_t _limit) const = 0;


    };
}