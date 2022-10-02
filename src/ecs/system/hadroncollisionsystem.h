#pragma once

#include <secs/secs.h>

#include "../components.h"


class HadronCollisionSystem
        : public secs::TypedEntitySystem<HadronCollisionComponent, TransformComponent>,
          public hadron::ICollisionListener
{
public:

    HadronCollisionSystem()
    {
        SetStepConfiguration(true, false);
        m_physicsWorld.RegisterListener(this);
    }

    ~HadronCollisionSystem() override
    {
        m_physicsWorld.UnregisterListener(this);
    }

    void PostUpdate(double delta) override
    {
        SECS_UNUSED(delta);
        m_physicsWorld.Step();
    }

    void process(double delta, const secs::Entity &e, HadronCollisionComponent &hcc, TransformComponent& tc) override
    {
        SECS_UNUSED(delta);
        SECS_UNUSED(e);
        const auto& p = tc.position;
        hcc.body->SetPosition(hadron::Vec2(p.GetX() + hcc.offset.GetX(), p.GetY() + hcc.offset.GetY()));
    }

    void Render(const secs::Entity &e) override
    {
        auto& hcc = GetComponent<HadronCollisionComponent>(e);
        const auto& aabb = hcc.body->GetAABB();
        float x1, y1, x2, y2;
        x1 = aabb.x;
        x2 = x1 + aabb.width;
        y1 = aabb.y;
        y2 = y1 + aabb.height;
        aether::graphics::draw_rectangle(x1, y1, x2, y2, aether::graphics::Color(uint8_t(0), uint8_t(255), uint8_t(255)), 2.f );
    }

    void OnEntityAdded( const secs::Entity& e ) override
    {
        auto& hcc = GetComponent<HadronCollisionComponent>(e);
        assert(hcc.body != nullptr);
        m_physicsWorld.RegisterBody(hcc.body);
        secs::Entity* eptr = new secs::Entity(e);
        hcc.body->SetUserData(static_cast<void*>(eptr));
    }

    void OnEntityRemoved( const secs::Entity& e ) override
    {
        auto& hcc = GetComponent<HadronCollisionComponent>(e);
        m_physicsWorld.UnregisterBody(hcc.body);
        auto eptr = static_cast<secs::Entity*>(hcc.body->GetUserData());
        delete eptr;
        delete hcc.body;
        hcc.body = nullptr;
        printf("cleanup\n"); fflush(0);
    }

    void OnCollisionEnter(hadron::Body &b1, hadron::Body &b2, hadron::CollisionResult result) override
    {
        auto e1 = getEntityFromBody(b1);
        auto e2 = getEntityFromBody(b2);
        handleCollisionEnter( e1, e2, result );
    }

    void OnCollisionExit(hadron::Body &b1, hadron::Body &b2) override
    {
        auto e1 = getEntityFromBody(b1);
        auto e2 = getEntityFromBody(b2);
        handleCollisionExit( e1, e2 );
    }

    void handleCollisionEnter( const secs::Entity& e1, const secs::Entity& e2, hadron::CollisionResult result )
    {
        secs::Entity ref1, ref2;
        if( entitiesHaveComponents<DoorComponent, PlayerComponent>(e1, e2, &ref1, &ref2) ) {
            m_hitDoor = ref1;
            m_isHittingDoor = true;
            m_hitDoorResult = result;
        }
    }

    void handleCollisionExit( const secs::Entity& e1, const secs::Entity& e2 )
    {
        secs::Entity ref1, ref2;
        if( entitiesHaveComponents<DoorComponent, PlayerComponent>(e1, e2, &ref1, &ref2) ) {
            m_isHittingDoor = false;
        }
    }

    bool isHittingDoor()
    {
        return m_isHittingDoor;
    }

    secs::Entity hittingDoor()
    {
        return m_hitDoor;
    }

    const hadron::CollisionResult& doorCollisionResult()
    {
        return m_hitDoorResult;
    }

private:

    template <typename C1, typename C2>
    bool entitiesHaveComponents(secs::Entity e1, secs::Entity e2, secs::Entity* ref1, secs::Entity* ref2)
    {
        bool check = false;
        if( HasComponent<C1>(e1) && HasComponent<C2>(e2) )
        {
            *ref1 = e1; *ref2 = e2;
            check = true;
        }
        else if( HasComponent<C1>(e2) && HasComponent<C2>(e1) )
        {
            *ref1 = e2; *ref2 = e1;
            check = true;
        }
        return check;
    }

    secs::Entity getEntityFromBody( hadron::Body& b )
    {
        return *(static_cast<secs::Entity*>(b.GetUserData()));
    }

    hadron::collision::World m_physicsWorld;

    secs::Entity m_hitDoor;
    bool m_isHittingDoor = false;
    hadron::CollisionResult m_hitDoorResult;

};
