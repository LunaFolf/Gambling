#pragma once
#include "Gambling/GameManager.h"
#include "Gambling/Scene.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"

class GameplayScene : public Scene {
public:
    GameManager* gameManager;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::Texture bulletsTexture;
    sf::Sprite bulletsSprite;

    float moneyDeltaCount = 0.f;
    int actualMoney = 0;
    int displayMoney = 0;

    sf::Texture moneyTexture;
    sf::Sprite moneySprite;

    sf::Texture gunTexture;
    sf::Sprite gunSprite;

    sf::Vector2f playerGunPos = {720.f / 2, 576.f - 32};
    sf::Vector2f rivalGunPos = {720.f / 2, 32.f};

    sf::Font font;
    sf::Text moneyText;
    sf::Text bulletsText;

    sf::Texture ltTexture;
    sf::Sprite ltSprite;

    sf::Texture rtTexture;
    sf::Sprite rtSprite;

    sf::Text ltText;
    sf::Text rtText;

    float aiAimDelta = 0.f;
    bool aiShootSelf = false;
    bool aiAiming = false;

    bool isGunVisible = false;
    bool isBulletsVisible = false;
    bool isMoneyVisible = false;

    bool isLTPromptVisible = false;
    bool isRTPromptVisible = false;

    bool tutorial = true;
    std::vector<bool> bullets = {};

    enum Difficulty {
        easy = 2,
        medium = 4,
        hard = 8
    };

    sf::Vector2f getMoneyDialoguePos() const;
    sf::Vector2f getBulletsDialoguePos() const;
    sf::Vector2f getGunDialoguePos() const;
    Difficulty currentDifficulty = easy;

    bool playersTurn = false;

    GameplayScene(GameManager* _gameManager);

    void updateBulletCount();
    void setMoney(int money);

    void aiTurn();
    void aiShoot();

    void doubleOrNothingPrompt();

    void start();
    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    void eventHandler(sf::Event& event);

    void generateBullets();
    void rotateMoveGun(float triggerPull);

    void toggleGunVisible(bool state);
    void toggleBulletsVisible(bool state);
    void toggleMoneyVisible(bool state);

    void toggleLTPrompt(bool state);
    void toggleRTPrompt(bool state);
};
