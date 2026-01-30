#pragma once
#include "Gambling/Scene.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"

class IntroScene : public Scene {
public:
    sf::SoundBuffer introSoundBuffer;
    sf::Sound introSound;

    IntroScene();

    void start();
    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    void eventHandler(sf::Event& event);
};
