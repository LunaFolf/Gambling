#pragma once
#include "Gambling/GameManager.h"
#include "Gambling/Scene.h"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"

class GameOverScene : public Scene {
public:
    GameManager* gameManager;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::Font font;
    std::vector<sf::Text> menuTexts{};

    std::string menuOptions[2] = { "Return to Menu", "Quit" };

    std::vector<sf::Text> GameOverStats{};

    std::string GameStats[4] = { "Shots fired: 15", "Blanks: 7", "Items used: 20", "Money Earned: 621" };

    std::string demoTextString = "Double or Nothing endless mode will be available in the full release,\n"
                                 "in addition to consumables, colour mode, and more...";
    sf::Text demoText;

    int selectedOption = 0;

    sf::Texture selectPromptTexture;
    sf::Sprite selectPromptSprite;

    bool fadingIn = true;
    float fadeTime = 1.5f;
    GameOverScene(GameManager* _gameManager);

    void start();
    void update(float deltaTime);
    void render(sf::RenderWindow& window);

    void eventHandler(sf::Event& event);
};
