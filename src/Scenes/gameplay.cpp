#include <cmath>
#include <iostream>
#include <ostream>
#include <Gambling/Scenes/gameplay.h>

#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"

GameplayScene::GameplayScene(GameManager* _gameManager) : Scene("Main Gameplay") {
    constexpr float padding = 8.f;

    gameManager = _gameManager;

    reloadBuffer.loadFromFile("assets/sfx/clipload1.wav");
    reloadSound.setBuffer(reloadBuffer);

    font.loadFromFile("assets/fonts/ithaca.ttf");
    font.setSmooth(false);
    ltTexture.loadFromFile("assets/sprites/ps/LeftTrigger2.png");
    ltSprite.setTexture(ltTexture);
    ltSprite.setScale(2.f, 2.f);
    ltSprite.setOrigin(ltTexture.getSize().x / 2.f, ltTexture.getSize().y / 2.f);
    ltSprite.setColor({255, 255, 255, 0});
    ltSprite.setPosition(720 * 0.25, 576.f / 2);

    ltText.setFont(font);
    ltText.setCharacterSize(32);
    ltText.setFillColor(sf::Color::Transparent);
    ltText.setOutlineColor(sf::Color::Transparent);
    ltText.setOutlineThickness(2.f);
    ltText.setString("Shoot Self");
    ltText.setOrigin(ltText.getLocalBounds().width / 2.f, ltText.getLocalBounds().height / 2.f);
    ltText.setPosition(ltSprite.getPosition().x, ltSprite.getPosition().y + ltText.getLocalBounds().height / 2.f + padding);

    rtTexture.loadFromFile("assets/sprites/ps/RightTrigger2.png");
    rtSprite.setTexture(rtTexture);
    rtSprite.setScale(2.f, 2.f);
    rtSprite.setOrigin(rtTexture.getSize().x / 2.f, rtTexture.getSize().y / 2.f);
    rtSprite.setColor({255, 255, 255, 0});
    rtSprite.setPosition(720 * 0.75, 576.f / 2);

    rtText.setFont(font);
    rtText.setCharacterSize(32);
    rtText.setFillColor(sf::Color::Transparent);
    rtText.setOutlineColor(sf::Color::Transparent);
    rtText.setOutlineThickness(2.f);
    rtText.setString("Shoot Gungler");
    rtText.setOrigin(rtText.getLocalBounds().width / 2.f, rtText.getLocalBounds().height / 2.f);
    rtText.setPosition(rtSprite.getPosition().x, rtSprite.getPosition().y + rtText.getLocalBounds().height / 2.f + padding);

    backgroundTexture.loadFromFile("assets/backgrounds/pleb.png");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(2.f, 2.f);
    backgroundSprite.setOrigin(backgroundTexture.getSize().x / 2.f, backgroundTexture.getSize().y / 2.f);
    backgroundSprite.setPosition(720.f / 2.f, 576.f / 2.f);

    bulletsTexture.loadFromFile("assets/sprites/LivesBackground.png");
    bulletsSprite.setTexture(bulletsTexture);
    bulletsSprite.setPosition(720.f - (188.f + padding), padding);
    bulletsSprite.setScale(2.f, 2.f);
    if (!isBulletsVisible) bulletsSprite.setColor({255, 255, 255, 0});

    moneyTexture.loadFromFile("assets/sprites/MoneyBackground.png");
    moneySprite.setTexture(moneyTexture);
    moneySprite.setPosition(padding, 576.f - (122.f + padding));
    moneySprite.setScale(2.f, 2.f);
    if (!isMoneyVisible) moneySprite.setColor({255, 255, 255, 0});

    moneyText.setFont(font);

    moneyText.setCharacterSize(32*2);
    moneyText.setFillColor(sf::Color::Transparent);
    moneyText.setOutlineColor(sf::Color::Transparent);
    moneyText.setOutlineThickness(2.f);

    bulletsText.setFont(font);

    bulletsText.setCharacterSize(32*2);
    bulletsText.setFillColor(sf::Color::Transparent);
    bulletsText.setOutlineColor(sf::Color::Transparent);
    bulletsText.setOutlineThickness(2.f);

    gunTexture.loadFromFile("assets/sprites/Revolver.png");
    gunSprite.setTexture(gunTexture);
    gunSprite.setScale(2.f, 2.f);
    gunSprite.setOrigin(11.f,89.f); // Pivot point for rotation
    gunSprite.setPosition(720.f / 2, 576.f - 32);
    gunSprite.setRotation(90.f);
    if (!isGunVisible) gunSprite.setColor({255, 255, 255, 0});

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
            gameManager->addMoneyEarned(-1000);

            this->addDialogue(new Dialogue(
                "This is your debt...\n"
                "If you want to leave here, you've got to pay it off...",
                this->getMoneyDialoguePos(),
                Dialogue::Voice::evilgungler,
                "assets/sprites/SpriteEVILRIVAL.png",
                1.f,
                [this]() {
                    toggleBulletsVisible(true);

                    this->addDialogue(new Dialogue(
                        "This is your bullet counter\n"
                        "The number of bullets left in the chamber are counted here...",
                        this->getBulletsDialoguePos(),
                        Dialogue::Voice::evilgungler,
                        "assets/sprites/SpriteEVILRIVAL.png",
                        1.f,
                        [this]() {
                            toggleGunVisible(true);

                            this->addDialogue(new Dialogue(
                                "And this is a gun...\n"
                                "Oh did I forgot to mention?\n"
                                "You loose... You die... *evil chuckle*",
                                this->getGunDialoguePos(),
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
                                        "assets/sprites/SpriteEVILRIVAL.png",
                                        1.f,
                                        [this]() {
                                            this->addDialogue(new Dialogue(
                                                "Ready? Let's start...",
                                                {8, (576.f / 2) - 74},
                                                Dialogue::Voice::evilgungler,
                                                "assets/sprites/SpriteEVILRIVAL.png",
                                                1.f,
                                                [this]() {
                                                    this->addDialogue(new Dialogue(
                                                        "First, I load some rounds into the gun...\n"
                                                        "Random order, random chance to be blank or live...",
                                                        this->getBulletsDialoguePos(),
                                                        Dialogue::Voice::evilgungler,
                                                        "assets/sprites/SpriteEVILRIVAL.png",
                                                        1.f,
                                                        [this]() {
                                                            generateBullets();

                                                            this->addDialogue(new Dialogue(
                                                                "And now... we shoot...\n"
                                                                "I'll be nice, let you go first...",
                                                                this->getGunDialoguePos(),
                                                                Dialogue::Voice::evilgungler,
                                                                "assets/sprites/SpriteEVILRIVAL.png",
                                                                1.f,
                                                                [this]() {
                                                                    toggleLTPrompt(true);
                                                                    toggleRTPrompt(true);

                                                                    tutorial = false;
                                                                    playersTurn = true;
                                                                }
                                                            ));
                                                        }
                                                    ));
                                                },
                                                true
                                            ));
                                        }
                                    ));
                                }
                            ));
                        }
                    ));
                }
            ));
        },
        true
    ));

    setMoney(0);
    currentDifficulty = medium;
}

sf::Vector2f GameplayScene::getBulletsDialoguePos() const {
    return {bulletsSprite.getPosition().x - 256, bulletsSprite.getPosition().y + bulletsSprite.getGlobalBounds().height};
}

sf::Vector2f GameplayScene::getMoneyDialoguePos() const {
    return {moneySprite.getPosition().x + moneySprite.getGlobalBounds().width - 96, moneySprite.getPosition().y - 96};
}

sf::Vector2f GameplayScene::getGunDialoguePos() const {
    return {gunSprite.getPosition().x - 142, gunSprite.getPosition().y - 182};
}

void GameplayScene::updateBulletCount() {
    bulletsText.setString(std::to_string(bullets.size()));
    bulletsText.setOrigin(bulletsText.getLocalBounds().width / 2.f, bulletsText.getLocalBounds().height / 2.f);
    bulletsText.setPosition(bulletsSprite.getPosition());
    bulletsText.move(61 * 2, 9);
}

void GameplayScene::setMoney(const int money) {
    actualMoney = money;
}

void GameplayScene::generateBullets() {
    bullets.clear();

    for (int i = currentDifficulty - 1; i >= 0; i--) {
        bool isBulletLive = rand() % 2 == 0;
        bullets.push_back(isBulletLive);

        reloadSound.setPitch(isBulletLive ? 1.25f : 0.75f);
        reloadSound.play();

        while (reloadSound.getStatus() == sf::SoundSource::Status::Playing) {}
    }

    for (int i = 0; i < bullets.size(); i++) {
        std::cout << bullets[i] << ((i < bullets.size() - 1) ? " | " : "");
    }
    std::cout << std::endl;

    updateBulletCount();
}

void GameplayScene::rotateMoveGun(const float triggerPull) {
    // 1 = self, -1 = rival, 0 = none

    float absolutePull = std::abs(triggerPull);

    if (absolutePull > 0.f) {
        sf::Vector2f targetPos = {720.f / 2.f, 576.f / 2.f}; // Center of screen
        sf::Vector2f& defaultPos = (tutorial || playersTurn) ? playerGunPos : rivalGunPos;
        // transpose from default position, to center, depending on how much the trigger is pulled
        sf::Vector2f delta = targetPos - defaultPos;
        sf::Vector2f newPos = defaultPos + (delta * absolutePull);
        gunSprite.setPosition(newPos);
        float selfAngle = (tutorial || playersTurn) ? 90.f : -90.f;
        float targetAngle = (triggerPull > 0.f) ? 180.f : 0.f;
        float newAngle = selfAngle + (targetAngle - selfAngle) * absolutePull;
        gunSprite.setRotation(newAngle);
    } else {
        sf::Vector2f& defaultPos = (tutorial || playersTurn) ? playerGunPos : rivalGunPos;
        gunSprite.setPosition(defaultPos);
        float selfAngle = (tutorial || playersTurn) ? 90.f : -90.f;
        gunSprite.setRotation(selfAngle);
    }
}

void GameplayScene::start() {
    Scene::start();

    gameManager->playAmbientSound();
    bullets.reserve(currentDifficulty);
}

void GameplayScene::update(const float deltaTime) {
    Scene::update(deltaTime);

    if (aiAiming) {
        rotateMoveGun(aiAimDelta);
        if (aiShootSelf) aiAimDelta -= deltaTime;
        else aiAimDelta += deltaTime;

        if (std::abs(aiAimDelta) >= 1.f) {
            aiAiming = false;
            aiAimDelta = 0.f;

            aiShoot();
        }
    }

    if (displayMoney != actualMoney) {
        moneyDeltaCount += deltaTime;
        if (moneyDeltaCount < .0065f) return;
        moneyDeltaCount = 0.f;
        if (displayMoney < actualMoney) displayMoney++;
        else displayMoney--;
        moneyText.setString(std::to_string(displayMoney));
        moneyText.setOrigin(moneyText.getLocalBounds().width / 2.f, moneyText.getLocalBounds().height / 2.f);
        moneyText.setPosition(moneySprite.getPosition());
        moneyText.move(92, 61);
    }
}

void GameplayScene::render(sf::RenderWindow& window) {
    window.draw(backgroundSprite);

    window.draw(bulletsSprite);
    window.draw(bulletsText);

    window.draw(gunSprite);

    Scene::render(window);

    window.draw(moneySprite);
    window.draw(moneyText);

    window.draw(ltSprite);
    window.draw(ltText);

    window.draw(rtSprite);
    window.draw(rtText);
}

void GameplayScene::doubleOrNothingPrompt() {
    toggleLTPrompt(false);
    toggleRTPrompt(false);
    toggleGunVisible(false);
    toggleBulletsVisible(false);
    toggleMoneyVisible(false);

    playersTurn = false;
    tutorial = true;

    this->addDialogue(new Dialogue(
        "Huh... you actually cleared your debt...\n"
        "I'll be honest I wasn't expecting that...\n"
        "Well a deals a deal, you can leave...\n"
        "Unless... Double or Nothing?",
        {8, 8},
        Dialogue::Voice::evilgungler,
        "assets/sprites/SpriteEVILRIVAL.png",
        1.f,
        [this]() {
            sceneManager->changeScene(7);
        },
        true
    ));
}

void GameplayScene::aiTurn() {
    rotateMoveGun(0);
    toggleGunVisible(true);

    this->addDialogue(new Dialogue(
        "Looks like it's my turn...",
        {8, 8},
        Dialogue::Voice::evilgungler,
        "assets/sprites/SpriteEVILRIVAL.png",
        1.f,
        [this]() {
            aiShootSelf = rand() % 2 == 0;
            std::cout << "shooting: " << (aiShootSelf ?"self":"rival") << std::endl;
            aiAiming = true;
        },
        true
    ));
}

void GameplayScene::aiShoot() {
    bool bulletIsLive = bullets.size() ? bullets.back() : false;

    bullets.erase(bullets.end() - 1);
    updateBulletCount();

    this->gameManager->setLastFiredBulletWasLive(bulletIsLive);

    if (aiShootSelf) {
        // Shoot self
        this->sceneManager->nextScene();
        toggleGunVisible(false);

        if (bulletIsLive) {
            gameManager->addShotsFired(1);
            gameManager->addMoneyEarned(100);
            gameManager->addRivalsKilled(1);

            actualMoney += 100;
            setMoney(actualMoney);

            if (actualMoney >= 0) {
                doubleOrNothingPrompt();
                return;
            }

            this->addDialogue(new Dialogue(
                "F*@!...\n"
                "Unfortunately for you, we have more gunglers than you can count...\n"
                "BRING IN GUNGLER #" + std::to_string(gameManager->rivalsKilled + 1) + "!",
                {8, 8},
                Dialogue::Voice::evilgungler,
                "assets/sprites/SpriteEVILRIVAL.png",
                1.f,
                [this]() {
                    playersTurn = true;
                    toggleLTPrompt(true);
                    toggleRTPrompt(true);
                    toggleGunVisible(true);

                    if (bullets.size() < 1) generateBullets();
                },
                true
            ));
        } else {
            this->addDialogue(new Dialogue(
                "Hmmm... You're turn, cretin...",
                {8, 8},
                Dialogue::Voice::evilgungler,
                "assets/sprites/SpriteEVILRIVAL.png",
                1.f,
                [this]() {
                    playersTurn = true;
                    toggleLTPrompt(true);
                    toggleRTPrompt(true);
                    toggleGunVisible(true);

                    if (bullets.size() < 1) generateBullets();
            },
            true
            ));
        }
    } else {
        // Shoot player
        this->sceneManager->nextScene();
        toggleGunVisible(false);

        if (bulletIsLive) {
            gameManager->addShotsFired(1);

            gameManager->addMoneyEarned(-200);

            actualMoney -= 200;
            setMoney(actualMoney);

            if (actualMoney >= 0) {
                doubleOrNothingPrompt();
                return;
            }

            this->addDialogue(new Dialogue(
                "* Z A P *\n"
                "What? You thought we'd let you get out your debt THAT easy?\n"
                "Finish the game!\n"
                "Oh, by the way, that revive cost you an extra $200.",
                {8, 8},
                Dialogue::Voice::evilgungler,
                "assets/sprites/SpriteEVILRIVAL.png",
                1.f,
                [this]() {
                    playersTurn = true;
                    toggleLTPrompt(true);
                    toggleRTPrompt(true);
                    toggleGunVisible(true);

                    if (bullets.size() < 1) generateBullets();
            },
            true
            ));
        } else {
            gameManager->addMoneyEarned(100);

            actualMoney -= 100;
            setMoney(actualMoney);

            if (actualMoney >= 0) {
                doubleOrNothingPrompt();
                return;
            }

            this->addDialogue(new Dialogue(
                "Huh... must be your lucky day...",
                {8, 8},
                Dialogue::Voice::evilgungler,
                "assets/sprites/SpriteEVILRIVAL.png",
                1.f,
                [this]() {
                    playersTurn = true;
                    toggleLTPrompt(true);
                    toggleRTPrompt(true);
                    toggleGunVisible(true);

                    if (bullets.size() < 1) generateBullets();
            },
            true
            ));
        }
    }

    rotateMoveGun(0);
}

void GameplayScene::eventHandler(sf::Event &event) {
    Scene::eventHandler(event);

    if (tutorial || !playersTurn) return;

     if (event.type == sf::Event::JoystickMoved || event.type == sf::Event::MouseButtonPressed) {
        float pull = event.joystickMove.position / 100;
        bool bulletIsLive = bullets.size() ? bullets.back() : false;

         if (event.mouseButton.button == sf::Mouse::Button::Left) pull = 1.f;
         else if (event.mouseButton.button == sf::Mouse::Button::Right) pull = -1.f;

         if (event.type == sf::Event::MouseButtonPressed) {
             event.joystickMove.axis = sf::Joystick::Z; // Hacky, yes... but functional... for now.
         }

        switch (event.joystickMove.axis) {
            case sf::Joystick::X: // Left stick, x
                break;
            case sf::Joystick::Y: // Left stick, y
                break;
            case sf::Joystick::Z: // Triggers, positive left, negative right

                // gunSprite.setRotation(pull * 90);

                rotateMoveGun(pull);

                if (std::abs(pull) < 0.9f) return;
                playersTurn = false;
                bullets.erase(bullets.end() - 1);
                updateBulletCount();

                this->gameManager->setLastFiredBulletWasLive(bulletIsLive);

                toggleLTPrompt(false);
                toggleRTPrompt(false);
                
                gameManager->addBulletsUsed(1);

                if (pull > 0.9f) {
                    // Shoot self
                    this->sceneManager->nextScene();
                    toggleGunVisible(false);

                    if (bulletIsLive) {
                        gameManager->addShotsFired(1);

                        gameManager->addMoneyEarned(-200);

                        actualMoney -= 200;
                        setMoney(actualMoney);

                        this->addDialogue(new Dialogue(
                            "* Z A P *\n"
                            "What? You thought we'd let you get out your debt THAT easy?\n"
                            "Finish the game!\n"
                            "Oh, by the way, that revive cost you an extra $200.",
                            {8, 8},
                            Dialogue::Voice::evilgungler,
                            "assets/sprites/SpriteEVILRIVAL.png",
                            1.f,
                            [this]() {
                                playersTurn = false;
                                toggleLTPrompt(false);
                                toggleRTPrompt(false);

                                if (bullets.size() < 1) generateBullets();

                                aiTurn();
                        },
            true
                        ));
                    } else {
                        gameManager->addMoneyEarned(200);

                        actualMoney += 200;
                        setMoney(actualMoney);

                        this->addDialogue(new Dialogue(
                            "What the... you better not be cheatin' cretin...",
                            {8, 8},
                            Dialogue::Voice::evilgungler,
                            "assets/sprites/SpriteEVILRIVAL.png",
                            1.f,
                            [this]() {
                                playersTurn = true;
                                toggleGunVisible(true);
                                toggleLTPrompt(true);
                                toggleRTPrompt(true);

                                if (bullets.size() < 1) generateBullets();
                        },
            true
                        ));
                    }

                    if (actualMoney >= 0) {
                        std::cout << "money: " << actualMoney << std::endl;
                        doubleOrNothingPrompt();
                        return;
                    }
                } else if (pull < -0.9f) {
                    // Shoot gungler
                    this->sceneManager->nextScene();
                    toggleGunVisible(false);

                    if (bulletIsLive) {
                        gameManager->addShotsFired(1);
                        gameManager->addMoneyEarned(100);
                        gameManager->addRivalsKilled(1);
                        
                        actualMoney += 100;
                        setMoney(actualMoney);

                        if (actualMoney >= 0) {
                            doubleOrNothingPrompt();
                            return;
                        }

                        this->addDialogue(new Dialogue(
                            "F*@!...\n"
                            "Unfortunately for you, we have more gunglers than you can count...\n"
                            "BRING IN GUNGLER #" + std::to_string(gameManager->rivalsKilled + 1) + "!",
                            {8, 8},
                            Dialogue::Voice::evilgungler,
                            "assets/sprites/SpriteEVILRIVAL.png",
                            1.f,
                            [this]() {
                                playersTurn = false;

                                if (bullets.size() < 1) generateBullets();

                                aiTurn();
                        },
            true
                        ));
                    } else {
                        this->addDialogue(new Dialogue(
                            "Ha, unlucky...",
                            {8, 8},
                            Dialogue::Voice::evilgungler,
                            "assets/sprites/SpriteEVILRIVAL.png",
                            1.f,
                            [this]() {
                                playersTurn = false;

                                if (bullets.size() < 1) generateBullets();

                                aiTurn();
                        },
            true
                        ));
                    }
                }

                rotateMoveGun(0);

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

    rotateMoveGun(0);

    if (isGunVisible && gunSprite.getColor().a < 255) gunSprite.setColor({255, 255, 255, 255});
    else if (!isGunVisible && gunSprite.getColor().a > 0) gunSprite.setColor({255, 255, 255, 0});
}

void GameplayScene::toggleBulletsVisible(const bool state) {
    isBulletsVisible = state;

    if (isBulletsVisible) {
        bulletsSprite.setColor({255, 255, 255, 255});
        bulletsText.setFillColor(sf::Color::Black);
        bulletsText.setOutlineColor(sf::Color::White);
    }
    else {
        bulletsSprite.setColor({255, 255, 255, 0});
        bulletsText.setFillColor(sf::Color::Transparent);
        bulletsText.setOutlineColor(sf::Color::Transparent);
    }
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

void GameplayScene::toggleLTPrompt(bool state) {
    isLTPromptVisible = state;

    if (isLTPromptVisible) {
        ltSprite.setColor({255, 255, 255, 255});
        ltText.setFillColor(sf::Color::Black);
        ltText.setOutlineColor(sf::Color::White);
    } else {
        ltSprite.setColor({255, 255, 255, 0});
        ltText.setFillColor(sf::Color::Transparent);
        ltText.setOutlineColor(sf::Color::Transparent);
    }
}

void GameplayScene::toggleRTPrompt(bool state) {
    isRTPromptVisible = state;

    if (isRTPromptVisible) {
        rtSprite.setColor({255, 255, 255, 255});
        rtText.setFillColor(sf::Color::Black);
        rtText.setOutlineColor(sf::Color::White);
    } else {
        rtSprite.setColor({255, 255, 255, 0});
        rtText.setFillColor(sf::Color::Transparent);
        rtText.setOutlineColor(sf::Color::Transparent);
    }
}