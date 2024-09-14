#pragma once
#include <framework/Actor.h>
#include "gameplay/HealthComponent.h"
namespace ly
{
	class SpaceShip : public Actor
	{
	public:
		SpaceShip(World* owningWord, const std::string& texturePath = "");
		virtual void Tick(float deltaTime) override;
		void SetVelocity(const sf::Vector2f& newVel);
		sf::Vector2f GetVelocity() const { return mVelocity; };
		virtual void Shoot();
		virtual void BeginPlay() override;
		virtual void ApplyDamage(float amt) override;
	private:
		virtual void OnHealthChanged(float amt, float health, float maxHealth);
		virtual void OnTakenDamage(float amt, float health, float maxHealth);
		virtual void Blow();
		sf::Vector2f mVelocity;
		HealtComponent healthComp;
	};
}