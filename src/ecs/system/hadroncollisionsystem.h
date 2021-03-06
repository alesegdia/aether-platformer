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
        setStepConfiguration(true, false);
        m_physicsWorld.registerListener(this);
    }

    ~HadronCollisionSystem() override
    {
        m_physicsWorld.unregisterListener(this);
    }

    void postUpdate(double delta) override
    {
        SECS_UNUSED(delta);
        m_physicsWorld.step();
    }

    void process(double delta, const secs::Entity &e, HadronCollisionComponent &hcc, TransformComponent& tc) override
    {
        SECS_UNUSED(delta);
        SECS_UNUSED(e);
        const auto& p = tc.position;
        hcc.body->setPosition(hadron::Vec2(p.x() + hcc.offset.x(), p.y() + hcc.offset.y()));
    }

    void render(const secs::Entity &e) override
    {
        auto& hcc = component<HadronCollisionComponent>(e);
        const auto& aabb = hcc.body->aabb();
        float x1, y1, x2, y2;
        x1 = aabb.x;
        x2 = x1 + aabb.width;
        y1 = aabb.y;
        y2 = y1 + aabb.height;
        aether::graphics::draw_rectangle(x1, y1, x2, y2, aether::graphics::Color(uint8_t(0), uint8_t(255), uint8_t(255)), 2.f );
    }

    void onAdded( const secs::Entity& e ) override
    {
        auto& hcc = component<HadronCollisionComponent>(e);
        assert(hcc.body != nullptr);
        m_physicsWorld.registerBody(hcc.body);
        secs::Entity* eptr = new secs::Entity(e);
        hcc.body->userData(static_cast<void*>(eptr));
    }

    void onRemoved( const secs::Entity& e ) override
    {
        auto& hcc = component<HadronCollisionComponent>(e);
        m_physicsWorld.unregisterBody(hcc.body);
        auto eptr = static_cast<secs::Entity*>(hcc.body->userData());
        delete eptr;
        delete hcc.body;
        hcc.body = nullptr;
        printf("cleanup\n"); fflush(0);
    }

    void onCollisionEnter(hadron::Body &b1, hadron::Body &b2, hadron::CollisionResult result) override
    {
        auto e1 = getEntityFromBody(b1);
        auto e2 = getEntityFromBody(b2);
        handleCollisionEnter( e1, e2, result );
    }

    void onCollisionExit(hadron::Body &b1, hadron::Body &b2) override
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
        if( hasComponent<C1>(e1) && hasComponent<C2>(e2) )
        {
            *ref1 = e1; *ref2 = e2;
            check = true;
        }
        else if( hasComponent<C1>(e2) && hasComponent<C2>(e1) )
        {
            *ref1 = e2; *ref2 = e1;
            check = true;
        }
        return check;
    }

    secs::Entity getEntityFromBody( hadron::Body& b )
    {
        return *(static_cast<secs::Entity*>(b.userData()));
    }

    hadron::collision::World m_physicsWorld;

    secs::Entity m_hitDoor;
    bool m_isHittingDoor = false;
    hadron::CollisionResult m_hitDoorResult;

};
