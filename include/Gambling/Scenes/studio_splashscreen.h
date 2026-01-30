#pragma once
#include "Gambling/Scene.h"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"

class StudioSplashScreenScene : public Scene {
public:
    sf::Texture logoTexture;
    sf::Sprite logoSprite;
    bool fadingIn = true;
    float fadeTime = 2.5f;
    StudioSplashScreenScene();

    void start();

    void update(float deltaTime);

    void render(sf::RenderWindow& window);
};
