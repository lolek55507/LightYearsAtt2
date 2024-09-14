#include "gameplay/HealthComponent.h"
#include "framework/Core.h"
namespace ly
{
	HealtComponent::HealtComponent(float health, float maxHealth)
		: mHealth{health},
		mMaxHealth{maxHealth}
	{

	}
	void HealtComponent::ChangeHealth(float amt)
	{
		if (amt == 0) return;
		if (mHealth == 0) return;

		mHealth += amt;
		if (mHealth < 0)
		{
			mHealth = 0;
		}

		if (mHealth > mMaxHealth)
		{
			mHealth = mMaxHealth;
		}

		if (amt < 0)
		{
			TakenDamage(-amt);
			if (mHealth <= 0)
			{
				HealthEmpty();
			}
		}
		
		onHealthChanged.Broadcast(amt, mHealth, mMaxHealth);
	}
	void HealtComponent::TakenDamage(float amt)
	{
		onTakenDamage.Broadcast(amt, mHealth, mMaxHealth);
	}
	void HealtComponent::HealthEmpty()
	{
		onHealthEmpty.Broadcast();
	}
}