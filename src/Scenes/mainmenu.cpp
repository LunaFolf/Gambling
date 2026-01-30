#include <iostream>
#include <ostream>
#include <Gambling/Scenes/mainmenu.h>

#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Window/Event.hpp"

MainMenuScene::MainMenuScene (GameManager* _gameManager) : Scene ("Main Menu") {
    gameManager = _gameManager;

    backgroundTexture.loadFromFile("assets/backgrounds/menu.png");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(2.f, 2.f);
    backgroundSprite.setColor({255, 255, 255, 0});

    titleTexture.loadFromFile("assets/sprites/placeholder_title.png");
    titleSprite.setTexture(titleTexture);
    titleSprite.setScale(2.f, 2.f);
    titleSprite.setPosition(720.f - (titleSprite.getGlobalBounds().width + 8), 8);
    titleSprite.setColor({255, 255, 255, 0});

    selectPromptTexture.loadFromFile("assets/sprites/ps/XButton.png");
    selectPromptSprite.setTexture(selectPromptTexture);
    selectPromptSprite.setScale(2.f, 2.f);
    selectPromptSprite.setColor({255, 255, 255, 0});

    font.loadFromFile("assets/fonts/ithaca.ttf");

    menuTexts.reserve(2);

    for (int i = 0; i < 2; i++) {
        std::string& stringText = menuOptions[i];

        auto& menuText = menuTexts.emplace_back();
        menuText.setFont(font);
        menuText.setString(stringText);
        menuText.setCharacterSize(64);
        menuText.setFillColor(sf::Color::Transparent);
        menuText.setOutlineColor(sf::Color::Transparent);
        menuText.setOutlineThickness(2.f);

        sf::Vector2f position = {
            720.f - (titleSprite.getGlobalBounds().width + 8) + 64,
            8 + (titleSprite.getGlobalBounds().height + 8)
        };

        if (i > 0) {
            position.x = menuTexts[i - 1].getPosition().x;
            position.x += menuTexts[i - 1].getGlobalBounds().width + 32;
        }

        menuText.setPosition(position);
    }
}

void MainMenuScene::start() {
    Scene::start();

    gameManager->stopAmbientSound();
}

void MainMenuScene::update (const float deltaTime) {
    Scene::update (deltaTime);

    if (fadingIn) {
        float percent = this->clock.getElapsedTime().asSeconds() / fadeTime;

        if (percent > 1.f) {
            percent = 1.f;

            titleSprite.setColor({255, 255, 255, 255});
            for (auto& text : menuTexts) {
                text.setFillColor(sf::Color::White);
                text.setOutlineColor(sf::Color::Black);
            }

            selectPromptSprite.setColor({255, 255, 255, 255});

            fadingIn = false;
        }

        backgroundSprite.setColor({255, 255, 255, static_cast<sf::Uint8>(255 * percent)});

        return;
    }

    sf::Vector2f position = menuTexts[selectedOption].getPosition();
    position.y += menuTexts[selectedOption].getGlobalBounds().height + 32;
    position.x =
        (menuTexts[selectedOption].getPosition().x +
            menuTexts[selectedOption].getGlobalBounds().width / 2.f) -
                selectPromptSprite.getGlobalBounds().width / 2.f;

    selectPromptSprite.setPosition(position);

}

void MainMenuScene::render (sf::RenderWindow& window) {
    Scene::render (window);
    window.draw(backgroundSprite);
    window.draw(titleSprite);

    for (auto& text : menuTexts) window.draw(text);

    window.draw(selectPromptSprite);
}

void MainMenuScene::eventHandler (sf::Event& event) {
    if (fadingIn) return;

    if (event.type == sf::Event::JoystickMoved) {
        const float pull = event.joystickMove.position / 100;
        int newSelectedOption = selectedOption;

        switch (event.joystickMove.axis) {
            case sf::Joystick::X: // Left stick, x
                break;
            case sf::Joystick::Y: // Left stick, y
                break;
            case sf::Joystick::Z: // Triggers, positive left, negative right
                break;
            case sf::Joystick::U: // Right stick, x
                break;
            case sf::Joystick::V: // Right stick, y
                break;
            case sf::Joystick::PovX: // DPAD x
                if (pull > 0.f) {
                    if (selectedOption < 1) newSelectedOption = 1;
                    else newSelectedOption = 0;
                }
                else if (pull < 0.f) {
                    if (selectedOption > 0) newSelectedOption = 0;
                    else newSelectedOption = 1;
                }

                menuTexts[selectedOption].setFillColor(sf::Color::White);
                menuTexts[selectedOption].setOutlineColor(sf::Color::Black);
                selectedOption = newSelectedOption;
                menuTexts[selectedOption].setFillColor(sf::Color::Black);
                menuTexts[selectedOption].setOutlineColor(sf::Color::White);
                break;
            case sf::Joystick::PovY: // DPAD y
                break;
            default: break;
        }
    } else if (event.type == sf::Event::JoystickButtonPressed) {
        if (event.joystickButton.button == 0) {
            switch (selectedOption) {
                case 0: sceneManager->nextScene(); break;
                case 1: sceneManager->_quit(); break;
            }
        }
    }

}