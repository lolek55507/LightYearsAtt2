#include "framework/PhysicsSystem.h"
#include <box2d/b2_contact.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>

#include <box2d/b2_body.h>
#include "framework/Actor.h"
#include "framework/MathUtility.h"
namespace ly
{
	unique<PhysicsSystem> PhysicsSystem::physicsSystem{ nullptr };

	PhysicsSystem& PhysicsSystem::Get()
	{
		if (!physicsSystem)
		{
			physicsSystem = std::move(unique<PhysicsSystem>{new PhysicsSystem});
		}

		return *physicsSystem;
	}

	void PhysicsSystem::Step(float deltaTime)
	{
		ProcessPendingRemoveListeners();
		mPhysicsWorld.Step(deltaTime, mVelocityIterations, mPositionsIterations);
	}

	b2Body* PhysicsSystem::AddListener(Actor* Listener)
	{
		if (Listener->isPendingDestory()) return nullptr;

		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(Listener);
		bodyDef.position.Set(Listener->GetActorLocation().x * GetPhysicsScale(), Listener->GetActorLocation().y * GetPhysicsScale());
		bodyDef.angle = DegreesToRadians(Listener->GetActorRotation());

		b2Body* body = mPhysicsWorld.CreateBody(&bodyDef);

		b2PolygonShape shape;
		auto bound = Listener->GetActorGlobalBounds();
		shape.SetAsBox(bound.width/2.f * GetPhysicsScale(), bound.height / 2.f * GetPhysicsScale());

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		fixtureDef.isSensor = true;

		body->CreateFixture(&fixtureDef);

		return body;
	}

	void PhysicsSystem::RemoveListener(b2Body* bodyToRemove)
	{
		mPendingRemoveListeners.insert(bodyToRemove);
	}

	void PhysicsSystem::CleanUp()
	{
		physicsSystem = std::move(unique<PhysicsSystem>{new PhysicsSystem});
	}

	PhysicsSystem::PhysicsSystem()
		: mPhysicsWorld{b2Vec2{0.f, 0.f}},
		mPhysicsScale{0.01f},
		mVelocityIterations{8},
		mPositionsIterations{3},
		mContactiListener{},
		mPendingRemoveListeners{}
	{
		mPhysicsWorld.SetContactListener(&mContactiListener);
		mPhysicsWorld.SetAllowSleeping(false);
	}

	void PhysicsSystem::ProcessPendingRemoveListeners()
	{
		for (auto listener : mPendingRemoveListeners)
		{
			mPhysicsWorld.DestroyBody(listener);
		}

		mPendingRemoveListeners.clear();
	}
	
	void PhysicsContactListener::BeginContact(b2Contact* contact)
	{
		Actor* ActorA = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
		Actor* ActorB = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);

		if (ActorA && !ActorA->isPendingDestory())
		{
			ActorA->OnActorBeginOverlap(ActorB);
		}
		if (ActorB && !ActorB->isPendingDestory())
		{
			ActorB->OnActorBeginOverlap(ActorA);
		}
	}

	void PhysicsContactListener::EndContact(b2Contact* contact)
	{
		Actor* ActorA = nullptr;
		Actor* ActorB = nullptr;

		if (contact->GetFixtureA() && contact->GetFixtureA()->GetBody())
		{
			ActorA = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
		}

		if (contact->GetFixtureB() && contact->GetFixtureB()->GetBody())
		{
			ActorB = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
		}

		if (ActorA && !ActorA->isPendingDestory())
		{
			ActorA->OnActorEndOverlap(ActorB);
		}
		if (ActorB && !ActorB->isPendingDestory())
		{
			ActorB->OnActorEndOverlap(ActorA);
		}
	}

}