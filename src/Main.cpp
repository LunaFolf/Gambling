#include <iostream>
#include <SFML/Graphics.hpp>

#include "Gambling/Scene.h"
#include "Gambling/Scenes/uon_splashscreen.h"


using namespace std;

int main() {
	// sf::Vector2i monitorRes(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);

	sf::Vector2i RESOLUTION(720.f, 576.f);
	sf::VideoMode VIDEO_MODE(RESOLUTION.x, RESOLUTION.y);
	sf::RenderWindow GAME_WINDOW(
		VIDEO_MODE,
		"5px penis",
		sf::Style::None
		);

	// Seed randomise function with the current time.
	srand(time(nullptr));

	sf::Texture texture;
	sf::Sprite sprite;

	texture.loadFromFile("Assets/demo.png");
	sprite.setTexture(texture);

	sf::Texture sansTexture;
	sf::Sprite sansSprite;

	sansTexture.loadFromFile("Assets/sans.png");
	sansSprite.setTexture(sansTexture);

	float playerXAccel = 0, playerYAccel = 0;

	sf::Clock clock;

	Scene* sceneList[1] = {
		new UONSplashscreenScene()
	};

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

			if (event.type == sf::Event::JoystickMoved) {
				switch (event.joystickMove.axis) {
					case sf::Joystick::Axis::X:
						playerXAccel = event.joystickMove.position;
						break;
					case sf::Joystick::Axis::Y:
						playerYAccel = event.joystickMove.position;
						break;
				}
			}
		}

		float deltaTime = clock.restart().asSeconds();

		if (abs(playerXAccel) < 20.f) playerXAccel = 0;
		if (abs(playerYAccel) < 20.f) playerYAccel = 0;

		sansSprite.move(playerXAccel * 2 * deltaTime, playerYAccel * 2 * deltaTime);

		GAME_WINDOW.clear();
		GAME_WINDOW.draw(sprite);
		GAME_WINDOW.draw(sansSprite);
		GAME_WINDOW.display();
	}

	return 0;
}