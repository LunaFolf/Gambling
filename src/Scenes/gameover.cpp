#include <iostream>
#include <ostream>
#include <Gambling/Scenes/gameover.h>
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Window/Event.hpp"

GameOverScene::GameOverScene (GameManager* _gameManager) : Scene ("Game Over") {
    gameManager = _gameManager;

    backgroundTexture.loadFromFile("assets/backgrounds/die.png");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(2.f, 2.f);
    backgroundSprite.setColor({ 255, 255, 255, 0 });

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
            200,
            200
        };

        if (i > 0) {
            position.y = menuTexts[i - 1].getPosition().y;
            position.y += menuTexts[i - 1].getGlobalBounds().height + 32;
        }

        menuText.setPosition(position);
    }

    GameOverStats.reserve(4);

    for (int i = 0; i < 4; i++) {

        auto& GameOverStat = GameOverStats.emplace_back();
        GameOverStat.setFont(font);
        GameOverStat.setCharacterSize(32);
        GameOverStat.setFillColor(sf::Color::Transparent);
        GameOverStat.setOutlineColor(sf::Color::Transparent);
        GameOverStat.setOutlineThickness(2.f);

        sf::Vector2f position = {
            8,
            8
        };

        if (i > 0) {
            position.y = GameOverStats[i - 1].getPosition().y;
            position.y += GameOverStats[i - 1].getGlobalBounds().height + 32;
        }

        GameOverStat.setPosition(position);
    }

    demoText.setFont(font);
    demoText.setString(demoTextString);
    demoText.setCharacterSize(32);
    demoText.setFillColor(sf::Color::Transparent);
    demoText.setOutlineColor(sf::Color::Transparent);
    demoText.setOutlineThickness(4.f);
    demoText.setPosition(8, 8 + (32 * 4));
}

void GameOverScene::start() {
    Scene::start();

    GameOverStats[0].setString("Shots fired: " + std::to_string(gameManager->shotsFired));
    GameOverStats[1].setString("Blanks: " + std::to_string(gameManager->bulletsUsed - gameManager->shotsFired));
    GameOverStats[2].setString("Items used: " + std::to_string(gameManager->itemsUsed));
    GameOverStats[3].setString("Money earned: " + std::to_string(gameManager->moneyEarned));
}

void GameOverScene::update (const float deltaTime) {
    Scene::update (deltaTime);

    if (fadingIn) {
        float percent = this->clock.getElapsedTime().asSeconds() / fadeTime;

        if (percent > 1.f) {
            percent = 1.f;

            for (auto& text : menuTexts) {
                text.setFillColor(sf::Color::White);
                text.setOutlineColor(sf::Color::Black);
            }

            for (auto& text2 : GameOverStats) {
                text2.setFillColor(sf::Color::White);
                text2.setOutlineColor(sf::Color::Black);
            }

            demoText.setFillColor(sf::Color::White);
            demoText.setOutlineColor(sf::Color::Black);

            selectPromptSprite.setColor({255, 255, 255, 255});

            fadingIn = false;
        }

        backgroundSprite.setColor({ 255, 255, 255, static_cast<sf::Uint8>(255 * percent) });

        return;
    }

    sf::Vector2f position = menuTexts[selectedOption].getPosition();
    position.y += menuTexts[selectedOption].getGlobalBounds().height - 20;
    position.x =
        (menuTexts[selectedOption].getPosition().x + menuTexts[selectedOption].getGlobalBounds().width + 16);

    selectPromptSprite.setPosition(position);
}

void GameOverScene::render (sf::RenderWindow& window) {
    Scene::render (window);

    window.draw(backgroundSprite);

    for (auto& text : menuTexts) window.draw(text);
    for (auto& text2 : GameOverStats) window.draw(text2);

    window.draw(demoText);

    window.draw(selectPromptSprite);
}

void GameOverScene::eventHandler (sf::Event& event) {
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
            case sf::Joystick::PovY: // DPAD x
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
            case sf::Joystick::PovX: // DPAD y
                break;
            default: break;
        }
    } else if (event.type == sf::Event::JoystickButtonPressed) {
        if (event.joystickButton.button == 0) {
            switch (selectedOption) {
                case 0: sceneManager->changeScene(3); break;
                case 1: sceneManager->_quit(); break;
            }
        }
    }

}