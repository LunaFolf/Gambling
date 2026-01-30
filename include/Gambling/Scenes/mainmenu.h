#pragma once
#include "Gambling/Scene.h"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"

class MainMenuScene : public Scene {
public:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::Texture titleTexture;
    sf::Sprite titleSprite;

    sf::Font font;
    std::vector<sf::Text> menuTexts{};

    std::string menuOptions[2] = { "Start", "Quit" };

    int selectedOption = 0;

    sf::Texture selectPromptTexture;
    sf::Sprite selectPromptSprite;

    bool fadingIn = true;
    float fadeTime = 1.5f;
    MainMenuScene();

    void start();
    void update(float deltaTime);
    void render(sf::RenderWindow& window);

    void eventHandler(sf::Event& event);
};
