#include <iostream>
#include <SFML/Graphics.hpp>

#include "Gambling/GameManager.h"
#include "Gambling/Scene.h"
#include "Gambling/Scenes/gameplay.h"
#include "Gambling/Scenes/intro.h"
#include "Gambling/Scenes/mainmenu.h"
#include "Gambling/Scenes/pegi_splashscreen.h"
#include "Gambling/Scenes/shoot.h"
#include "Gambling/Scenes/studio_splashscreen.h"
#include "Gambling/Scenes/ui_test.h"
#include "Gambling/Scenes/uon_splashscreen.h"


using namespace std;

int main() {
	sf::Vector2i RESOLUTION(720.f, 576.f);
	sf::VideoMode VIDEO_MODE(RESOLUTION.x, RESOLUTION.y);
	sf::RenderWindow GAME_WINDOW(
		VIDEO_MODE,
		"INSERT GAME NAME HERE :3",
		sf::Style::None
		);

	GAME_WINDOW.display();

	// system("pause");

	GAME_WINDOW.setMouseCursorVisible(false);

	srand(time(nullptr));

	sf::RectangleShape bg_rect(sf::Vector2f(RESOLUTION.x, RESOLUTION.y));
	bg_rect.setFillColor(sf::Color::Black);
	sf::Clock deltaClock;

	auto* gameManager = new GameManager();

	auto* sceneManager = new SceneManager(&GAME_WINDOW);
	sceneManager->addScene(new UONSplashscreenScene());
	sceneManager->addScene(new StudioSplashScreenScene());
	sceneManager->addScene(new PEGISplashscreenScene());
	sceneManager->addScene(new MainMenuScene());
	sceneManager->addScene(new IntroScene());
	sceneManager->addScene(new GameplayScene(gameManager));
	sceneManager->addScene(new ShootScene(gameManager));

	sceneManager->changeScene(5);

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