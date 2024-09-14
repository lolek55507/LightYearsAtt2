#include "spaceship/SpaceShip.h"
#include "gameplay/HealthComponent.h"
#include <functional>	
#include <iostream>

namespace ly
{
	SpaceShip::SpaceShip(World* owningWord, const std::string& texturePath)
		: Actor{owningWord, texturePath},
		mVelocity{},
		healthComp{100.f, 100.f}
	{
	}
	void SpaceShip::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		AddActorLocationOffset(GetVelocity() * deltaTime);
	}
	void SpaceShip::SetVelocity(const sf::Vector2f& newVel)
	{
		mVelocity = newVel;
	}
	void SpaceShip::Shoot()
	{
	}
	void SpaceShip::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablePhysics(true);
		
		healthComp.onHealthChanged.BindAction(GetWeakRef(), &SpaceShip::OnHealthChanged);
		healthComp.onTakenDamage.BindAction(GetWeakRef(), &SpaceShip::OnTakenDamage);
		healthComp.onHealthEmpty.BindAction(GetWeakRef(), &SpaceShip::Blow);
	}
	void SpaceShip::ApplyDamage(float amt)
	{
		healthComp.ChangeHealth(-amt);
	}
	void SpaceShip::OnHealthChanged(float amt, float health, float maxHealth)
	{
		LOG("health changed by: %f, and is now: %f/%f", amt, health, maxHealth);
	}
	void SpaceShip::OnTakenDamage(float amt, float health, float maxHealth)
	{
		
	}
	void SpaceShip::Blow()
	{
		Destroy();
	}
}