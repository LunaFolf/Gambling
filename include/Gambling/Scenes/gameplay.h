#pragma once
#include "Gambling/Scene.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"

class GameplayScene : public Scene {
public:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::Texture livesTextures;
    sf::Sprite livesSprite;

    sf::Texture moneyTexture;
    sf::Sprite moneySprite;

    sf::Texture gunTexture;
    sf::Sprite gunSprite;

    sf::Vector2f playerGunPos = {720.f / 2, 576.f - 32};
    sf::Vector2f rivalGunPos = {720.f / 2, 32.f};

    sf::Font font;
    sf::Text moneyText;

    bool isGunVisible = false;
    bool isLivesVisible = false;
    bool isMoneyVisible = false;

    bool darkMode = false;
    std::vector<bool> shells = {};

    enum Difficulty {
        easy = 2,
        medium = 4,
        hard = 8
    };

    Difficulty currentDifficulty = easy;

    bool playersTurn = true;

    GameplayScene();

    void setMoney(int money);

    void start();
    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    void eventHandler(sf::Event& event);

    void generateShells();
    void rotateMoveGun(float triggerPull);

    void toggleGunVisible(bool state);
    void toggleLivesVisible(bool state);
    void toggleMoneyVisible(bool state);
};
