#include <cmath>
#include <iostream>
#include <ostream>
#include <Gambling/Scenes/gameplay.h>

#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"

int temp = 0;

GameplayScene::GameplayScene() : Scene("Main Gameplay") {
    constexpr float padding = 8.f;

    backgroundTexture.loadFromFile("assets/backgrounds/pleb.png");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(2.f, 2.f);
    backgroundSprite.setOrigin(backgroundTexture.getSize().x / 2.f, backgroundTexture.getSize().y / 2.f);
    backgroundSprite.setPosition(720.f / 2.f, 576.f / 2.f);

    livesTextures.loadFromFile("assets/sprites/LivesBackground.png");
    livesSprite.setTexture(livesTextures);
    livesSprite.setPosition(720.f - (188.f + padding), padding);
    livesSprite.setScale(2.f, 2.f);
    if (!isLivesVisible) livesSprite.setColor({255, 255, 255, 0});

    moneyTexture.loadFromFile("assets/sprites/MoneyBackground.png");
    moneySprite.setTexture(moneyTexture);
    moneySprite.setPosition(padding, 576.f - (122.f + padding));
    moneySprite.setScale(2.f, 2.f);
    if (!isMoneyVisible) moneySprite.setColor({255, 255, 255, 0});

    font.loadFromFile("assets/fonts/ithaca.ttf");
    moneyText.setFont(font);

    moneyText.setCharacterSize(32*2);
    moneyText.setFillColor(sf::Color::Transparent);
    moneyText.setOutlineColor(sf::Color::Transparent);
    moneyText.setOutlineThickness(2.f);

    gunTexture.loadFromFile("assets/sprites/Revolver.png");
    gunSprite.setTexture(gunTexture);
    gunSprite.setScale(2.f, 2.f);
    gunSprite.setOrigin(11.f,89.f); // Pivot point for rotation
    gunSprite.setPosition(720.f / 2, 576.f - 32);
    gunSprite.setRotation(90.f);
    if (!isGunVisible) gunSprite.setColor({255, 255, 255, 0});

    std::cout << "Dialogue 1" << std::endl;

    this->addDialogue(new Dialogue(
        "Oh? I see... you must be the cretin that couldn't pay their tab...\n"
        "*tut tut tut* Who comes to a Casino with an empty wallet?\n"
        "Oh well... You can play a different game, with me...",
        {8, 8},
        Dialogue::Voice::evilgungler,
        "assets/sprites/SpriteEVILRIVAL.png",
        1.f,
        [this]() {
            toggleMoneyVisible(true);
            setMoney(-1000);

            std::cout << "Dialogue 2" << std::endl;

            this->addDialogue(new Dialogue(
                "This is your debt...\n"
                "If you want to leave here, you've got to pay it off...",
                {moneySprite.getPosition().x + moneySprite.getGlobalBounds().width, moneySprite.getPosition().y},
                Dialogue::Voice::evilgungler,
                "assets/sprites/SpriteEVILRIVAL.png",
                1.f,
                [this]() {
                    toggleLivesVisible(true);

                    std::cout << "Dialogue 3" << std::endl;

                    this->addDialogue(new Dialogue(
                        "This is your bullet counter\n"
                        "The number of bullets left in the chamber are counted here...",
                        {livesSprite.getPosition().x - 128, livesSprite.getPosition().y + livesSprite.getGlobalBounds().height},
                        Dialogue::Voice::evilgungler,
                        "assets/sprites/SpriteEVILRIVAL.png",
                        1.f,
                        [this]() {
                            toggleGunVisible(true);

                            this->addDialogue(new Dialogue(
                                "And this is a gun...\n"
                                "Oh did I forgot to mention?\n"
                                "You loose... You die... *evil chuckle*",
                                {gunSprite.getPosition().x - 128, gunSprite.getPosition().y - 148},
                                Dialogue::Voice::evilgungler,
                                "assets/sprites/SpriteEVILRIVAL.png",
                                1.f,
                                [this]() {
                                    this->addDialogue(new Dialogue(
                                        "The game is simple... Russian Roulette.\n"
                                        "Each round you survive, you pay off some of your debt.\n"
                                        "Win enough rounds, and we'll let you leave here... no tricks...",
                                        {8, (576.f / 2) - 74},
                                        Dialogue::Voice::evilgungler,
                                        "assets/sprites/SpriteEVILRIVAL.png"
                                    ));
                                }
                            ));
                        }
                    ));
                }
            ));
        }
    ));
}

void GameplayScene::setMoney(const int money) {
    moneyText.setString(std::to_string(money));
    moneyText.setOrigin(moneyText.getLocalBounds().width / 2.f, moneyText.getLocalBounds().height / 2.f);
    moneyText.setPosition(moneySprite.getPosition());
    moneyText.move(92, 61);
}

void GameplayScene::generateShells() {
    shells.clear();

    shells.reserve(currentDifficulty);

    for (int i = 0; i < currentDifficulty; i++) {
        bool isShellLive = rand() % 2 == 0;
        shells.push_back(isShellLive);
    }

    for (int i = 0; i < shells.size(); i++) {
        std::cout << shells[i] << ((i < shells.size() - 1) ? " | " : "");
    }
    std::cout << std::endl;
}

void GameplayScene::rotateMoveGun(const float triggerPull) {
    if (!isGunVisible) return;
    // 1 = self, -1 = rival, 0 = none

    float absolutePull = std::abs(triggerPull);

    if (absolutePull > 0.f) {
        sf::Vector2f targetPos = {720.f / 2.f, 576.f / 2.f}; // Center of screen
        sf::Vector2f& defaultPos = playersTurn ? playerGunPos : rivalGunPos;
        // transpose from default position, to center, depending on how much the trigger is pulled
        sf::Vector2f delta = targetPos - defaultPos;
        sf::Vector2f newPos = defaultPos + (delta * absolutePull);
        gunSprite.setPosition(newPos);
        float selfAngle = playersTurn ? 90.f : -90.f;
        float targetAngle = (triggerPull > 0.f) ? 180.f : 0.f;
        float newAngle = selfAngle + (targetAngle - selfAngle) * absolutePull;
        gunSprite.setRotation(newAngle);
    } else {
        sf::Vector2f& defaultPos = playersTurn ? playerGunPos : rivalGunPos;
        gunSprite.setPosition(defaultPos);
        float selfAngle = playersTurn ? 90.f : -90.f;
        gunSprite.setRotation(selfAngle);
    }
}

void GameplayScene::start() {
    Scene::start();
    
    setMoney(0);
    currentDifficulty = easy;
    generateShells();
}

void GameplayScene::update(const float deltaTime) {
    Scene::update(deltaTime);
}

void GameplayScene::render(sf::RenderWindow& window) {
    window.draw(backgroundSprite);

    Scene::render(window);

    window.draw(livesSprite);
    window.draw(moneySprite);
    window.draw(moneyText);
    window.draw(gunSprite);
}

void GameplayScene::eventHandler(sf::Event &event) {
    Scene::eventHandler(event);

    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::Space:
                generateShells();
                break;
            case sf::Keyboard::Up:
                currentDifficulty = static_cast<Difficulty>(currentDifficulty * 2);
                break;
            case sf::Keyboard::Down:
                currentDifficulty = static_cast<Difficulty>(currentDifficulty / 2);
                break;
            default:
                break;
        }
    }
    else if (event.type == sf::Event::JoystickMoved) {
        const float pull = event.joystickMove.position / 100;

        switch (event.joystickMove.axis) {
            case sf::Joystick::X: // Left stick, x
                break;
            case sf::Joystick::Y: // Left stick, y
                break;
            case sf::Joystick::Z: // Triggers, positive left, negative right

                // gunSprite.setRotation(pull * 90);

                rotateMoveGun(pull);

                break;
            case sf::Joystick::U: // Right stick, x
                break;
            case sf::Joystick::V: // Right stick, y
                break;
            case sf::Joystick::PovX: // DPAD x
                break;
            case sf::Joystick::PovY: // DPAD y
                break;
            default: break;
        }
    }
}

void GameplayScene::toggleGunVisible(const bool state) {
    isGunVisible = state;

    if (isGunVisible && gunSprite.getColor().a < 255) gunSprite.setColor({255, 255, 255, 255});
    else if (!isGunVisible && gunSprite.getColor().a > 0) gunSprite.setColor({255, 255, 255, 0});
}

void GameplayScene::toggleLivesVisible(const bool state) {
    isLivesVisible = state;

    if (isLivesVisible) livesSprite.setColor({255, 255, 255, 255});
    else livesSprite.setColor({255, 255, 255, 0});
}

void GameplayScene::toggleMoneyVisible(const bool state) {
    isMoneyVisible = state;

    if (isMoneyVisible) {
        moneySprite.setColor({255, 255, 255, 255});
        moneyText.setFillColor(sf::Color::Black);
        moneyText.setOutlineColor(sf::Color::White);
    }
    else {
        moneySprite.setColor({255, 255, 255, 0});
        moneyText.setFillColor(sf::Color::Transparent);
        moneyText.setOutlineColor(sf::Color::Transparent);
    }
}
