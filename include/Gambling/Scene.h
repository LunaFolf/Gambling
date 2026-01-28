#pragma once
#include <string>

#include "SceneManager.h"

class Scene {
private:
public:
    SceneManager* sceneManager;
    sf::Clock clock;
    std::string name;

    Scene(std::string _name);
    void setSceneManager(SceneManager* _sceneManager);

    virtual void start();
    virtual void update(float deltaTime);
    virtual void render(sf::RenderWindow& window);
    virtual void eventHandler(sf::Event& event);
};
