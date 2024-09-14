#include <box2d/b2_body.h>
#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/AssetsManager.h"
#include "framework/MathUtility.h"
#include "framework/World.h"
#include "framework/PhysicsSystem.h"

namespace ly
{
	Actor::Actor(World* owningWorld, const std::string& texturePath)
		: mOwningWorld{owningWorld},
		mHasBeganPlay{false},
		mSprite{},
		mTexture{},
		mPhysicBody{nullptr},
		mPhysicsEnabled{false},
		mTeamID{GetNeturalTeamID()}
	{
		SetTexture(texturePath);
	}
	Actor::~Actor()
	{
		// LOG("Actor Destroyed");
	}
	void Actor::BeginPlayInternal()
	{
		if (!mHasBeganPlay)
		{
			mHasBeganPlay = true;
			BeginPlay();
		}
	}
	void Actor::TickInternal(float deltaTime)
	{
		if (!isPendingDestory())
		{
			Tick(deltaTime);
		}
	}
	void Actor::BeginPlay()
	{

	}
	void Actor::Tick(float deltaTime)
	{

	}
	void Actor::SetTexture(const std::string& texturePath)
	{
		mTexture = AssetManager::Get().LoadTexture(texturePath);
		if (!mTexture) return;
		mSprite.setTexture(*mTexture);

		int textureWidth = mTexture->getSize().x;
		int textureHeight = mTexture->getSize().y;

		mSprite.setTextureRect(sf::IntRect{ sf::Vector2i{}, sf::Vector2i{textureWidth, textureHeight } });
		CenterPivot();
	}
	void Actor::Render(sf::RenderWindow& window)
	{
		if (isPendingDestory())
			return;
		window.draw(mSprite);
	}
	void Actor::SetActorLocation(const sf::Vector2f& newLoc)
	{
		mSprite.setPosition(newLoc);
		UpdatePhysicsTransform();
	}
	void Actor::SetActorRotation(float newRot)
	{
		mSprite.setRotation(newRot);
		UpdatePhysicsTransform();
	}
	void Actor::AddActorLocationOffset(const sf::Vector2f& offsetAmt)
	{
		SetActorLocation(GetActorLocation() + offsetAmt);
	}
	void Actor::AddActorRotationOffset(float offsetAmt)
	{
		SetActorRotation(GetActorRotation() + offsetAmt);
	}
	sf::Vector2f Actor::GetActorLocation() const
	{
		return mSprite.getPosition();
	}
	float Actor::GetActorRotation() const
	{
		return mSprite.getRotation();
	}
	sf::Vector2f Actor::GetActorForwardDirection() const
	{
		return RotationToVector(GetActorRotation());
	}
	sf::Vector2f Actor::GetActorRigthDirection() const
	{
		return RotationToVector(GetActorRotation() + 90.f);
	}
	sf::Vector2u Actor::GetWindowSize() const
	{
		return mOwningWorld->GetWindowSize();
	}
	bool Actor::IsOtherHostile(Actor* other) const
	{
		if (GetTeamId() == GetNeturalTeamID() || other->GetTeamId() == GetNeturalTeamID())
		{
			return false;
		}
		return GetTeamId() != other->GetTeamId();
	}
	void Actor::ApplyDamage(float amt)
	{
		
	}
	void Actor::InitializePhysics()
	{
		if (!mPhysicBody)
		{
		mPhysicBody = PhysicsSystem::Get().AddListener(this);
		}
	}
	void Actor::UnInitializePhysics()
	{
	if (mPhysicBody)
	{
		PhysicsSystem::Get().RemoveListener(mPhysicBody);
		mPhysicBody = nullptr;
	}
	}
	void Actor::UpdatePhysicsTransform()
	{
		if (mPhysicBody)
		{
			float physicsScale = PhysicsSystem::Get().GetPhysicsScale();
			b2Vec2 pos{ GetActorLocation().x * physicsScale, GetActorLocation().y * physicsScale};
			float rotation = DegreesToRadians(GetActorRotation());

			mPhysicBody->SetTransform(pos, rotation);
		}
	}
	void Actor::CenterPivot()
	{
		sf::FloatRect bound = mSprite.getGlobalBounds();
		mSprite.setOrigin(bound.width / 2.f, bound.height / 2.f);
	}
	bool Actor::IsActorOutOfWindowBounds() const
	{
		float windowWidth = GetWorld()->GetWindowSize().x;
		float windowHeight = GetWorld()->GetWindowSize().y;

		float width = GetActorGlobalBounds().width;
		float height = GetActorGlobalBounds().height;

		sf::Vector2f actorPos = GetActorLocation();

		if (actorPos.x < -width)
		{
			return true;
		}

		if (actorPos.x > windowWidth + width)
		{
			return true;
		}
		if (actorPos.y < -height)
		{
			return true;
		}

		return false;

	}
	void Actor::SetEnablePhysics(bool enable)
	{
		mPhysicsEnabled = enable;
		if (mPhysicsEnabled)
		{
			InitializePhysics();
		}
		else
		{
			UnInitializePhysics();
		}
	}
	void Actor::OnActorBeginOverlap(Actor* other)
	{
		LOG("Overlapped");
	}
	void Actor::OnActorEndOverlap(Actor* other)
	{
		LOG("Overlappe finished");
	}
	void Actor::Destroy()
	{
		UnInitializePhysics();
		Object::Destroy();
	}
	sf::FloatRect Actor::GetActorGlobalBounds() const
	{
		return mSprite.getGlobalBounds();
	}
}