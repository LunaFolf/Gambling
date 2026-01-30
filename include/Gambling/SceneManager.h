#pragma once
#include <vector>

#include "SFML/Graphics/RenderWindow.hpp"

class Scene;

class SceneManager {
private:
    sf::RenderWindow* gameWindow;
    std::vector<Scene*> scenes;
    int activeSceneIndex = -1;
public:
    SceneManager(sf::RenderWindow* _gameWindow);

    void addScene(Scene* scene);

    void update(float deltaTime);
    void render(sf::RenderWindow& window);

    void changeScene(int index);

    void eventHandler(sf::Event& event);

    void _quit();
};
