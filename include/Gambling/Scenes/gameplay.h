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

    sf::Font font;
    sf::Text moneyText;

    bool darkMode = false;
    std::vector<bool> shells = {};

    GameplayScene();

    void setMoney(int money);

    void start();
    void update(float deltaTime);
    void render(sf::RenderWindow& window);

    void generateShells();
};
