#include "Slinky/Dynamics/World.hpp"

namespace Slinky
{
    World::World(const Math::Vector3& _gravity)
        : m_gravity(_gravity)
    {
    }

    World::~World()
    {
    }

    void World::Step(float _dt)
    {
        for (auto& body : m_bodies)
        {
            body->ApplyForce(m_gravity * body->Mass());
            body->Integrate(_dt);
        }
    }

    RigidBody* World::CreateBody(const RigidBody& _body)
    {
        m_bodies.push_back(std::make_shared<RigidBody>(_body));
        return m_bodies.back().get();
    }

    const std::vector<std::shared_ptr<RigidBody>>& World::Bodies() const
    {
        return m_bodies;
    }
}