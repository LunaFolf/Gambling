#pragma once
#include "Gambling/GameManager.h"
#include "Gambling/Scene.h"

class ShootScene : public Scene {
public:
    GameManager* gameManager;

    ShootScene(GameManager* _gameManager);

    sf::SoundBuffer liveBuffer;
    sf::SoundBuffer blankBuffer;
    sf::Sound liveSound;
    sf::Sound blankSound;

    void start();
    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    void eventHandler(sf::Event& event);
};