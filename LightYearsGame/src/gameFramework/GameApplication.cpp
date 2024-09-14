#include "gameFramework/gameApplication.h"
#include"framework/World.h"
#include "framework/Actor.h"
#include "framework/AssetsManager.h"
#include "player/PlayerSpaceShip.h"
#include "config.h"
ly::Application* GetApplication()
{
	return new ly::GameApplication();
}

namespace ly
{
	GameApplication::GameApplication()
		: Application{600, 980, "Light Years" ,sf::Style::Titlebar | sf::Style::Close}
	{
		AssetManager::Get().SetAssetRootDirectory(GetResourceDir());
	weak<World> newWorld = LoadWorld<World>();
	testPlayerSpaceShip = newWorld.lock()->SpawnActor<PlayerSpaceship>();
	testPlayerSpaceShip.lock()->SetActorLocation(sf::Vector2f(300.f, 490.f));

	weak<SpaceShip> testSpaceship = newWorld.lock()->SpawnActor<SpaceShip>();
	testSpaceship.lock()->SetTexture("SpaceShooterRedux/PNG/playerShip1_blue.png");
	testSpaceship.lock()->SetActorLocation(sf::Vector2f{ 100.f, 50.f });
	testSpaceship.lock()->SetTeamID(2);

	counter = 0.f;
	}

	void GameApplication::Tick(float deltaTime)
	{
		counter += deltaTime;
		/*if (counter > 10.f)
		{
			if (!testPlayerSpaceShip.expired())
			{
				testPlayerSpaceShip.lock()->Destroy();
			}
		}*/



	}

}