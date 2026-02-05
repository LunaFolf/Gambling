#include <iostream>
#include <SFML/Graphics.hpp>

#include "Gambling/GameManager.h"
#include "Gambling/Scene.h"
#include "Gambling/Scenes/gameplay.h"
#include "Gambling/Scenes/intro.h"
#include "Gambling/Scenes/mainmenu.h"
#include "Gambling/Scenes/gameover.h"
#include "Gambling/Scenes/pegi_splashscreen.h"
#include "Gambling/Scenes/shoot.h"
#include "Gambling/Scenes/studio_splashscreen.h"
#include "Gambling/Scenes/ui_test.h"
#include "Gambling/Scenes/uon_splashscreen.h"

#include "steam/steam_api.h"


using namespace std;

int main() {
	SteamAPI_Init();

	int numAchievements = SteamUserStats()->GetNumAchievements();
	for ( int i = 0; i < numAchievements; ++i )
	{
		const char *achName = SteamUserStats()->GetAchievementName( i );
		if ( achName && achName != "ACH_WIN_100_GAMES" )
		{
			SteamUserStats()->ClearAchievement("ACH_TRAVEL_FAR_SINGLE");
		}
	}

	SteamUserStats()->StoreStats();

	sf::Vector2u RESOLUTION(720, 576);
	sf::VideoMode VIDEO_MODE = sf::VideoMode::getDesktopMode();
	sf::RenderWindow GAME_WINDOW(
		VIDEO_MODE,
		"Chamberlocked",
		sf::Style::None
		);

	sf::View GAME_VIEW(
		sf::FloatRect(0.f, 0.f, RESOLUTION.x, RESOLUTION.y)
	);

	float windowRatio = static_cast<float>(VIDEO_MODE.width) / static_cast<float>(VIDEO_MODE.height);
	float viewRatio = static_cast<float>(RESOLUTION.x) / static_cast<float>(RESOLUTION.y);
	float sizeX = 1.f, sizeY = 1.f, posX = 0.f, posY = 0.f;

	if (windowRatio > viewRatio)
	{
		sizeX = viewRatio / windowRatio;
		posX = (1.f - sizeX) / 2.f;
	}
	else
	{
		sizeY = windowRatio / viewRatio;
		posY = (1.f - sizeY) / 2.f;
	}

	GAME_VIEW.setViewport({posX, posY, sizeX, sizeY});
	GAME_WINDOW.setView(GAME_VIEW);

	GAME_WINDOW.setMouseCursorVisible(false);

	srand(time(nullptr));

	sf::RectangleShape bg_rect(sf::Vector2f(RESOLUTION.x, RESOLUTION.y));
	bg_rect.setFillColor(sf::Color::Black);
	sf::Clock deltaClock;

	auto* gameManager = new GameManager();

	gameManager->playAmbientSound();

	auto* sceneManager = new SceneManager(&GAME_WINDOW);
	sceneManager->addScene(new UONSplashscreenScene());
	sceneManager->addScene(new StudioSplashScreenScene());
	sceneManager->addScene(new PEGISplashscreenScene());
	// sceneManager->addScene(new UITestScene());
	sceneManager->addScene(new MainMenuScene(gameManager));
	sceneManager->addScene(new IntroScene());
	sceneManager->addScene(new GameplayScene(gameManager));
	sceneManager->addScene(new ShootScene(gameManager));
	sceneManager->addScene(new GameOverScene(gameManager));

	sceneManager->changeScene(0);

	// Main Loop
	while (GAME_WINDOW.isOpen()) {

		sf::Event event;
		while (GAME_WINDOW.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				GAME_WINDOW.close();
			}

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					GAME_WINDOW.close();
				}
			}

			sceneManager->eventHandler(event);
		}

		float deltaTime = deltaClock.restart().asSeconds();

		sceneManager->update(deltaTime);

		GAME_WINDOW.clear();
		GAME_WINDOW.draw(bg_rect);
		sceneManager->render(GAME_WINDOW);
		GAME_WINDOW.display();
	}

	return 0;
}