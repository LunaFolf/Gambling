#pragma once
#include "Gambling/Scene.h"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"

class PEGISplashscreenScene : public Scene {
public:
    sf::Texture logoTexture;
    sf::Sprite logoSprite;
    bool fadingIn = true;
    float fadeTime = 2.5f;
    PEGISplashscreenScene();

    void start();

    void update(float deltaTime);

    void render(sf::RenderWindow& window);

    void eventHandler(sf::Event& event);
};
