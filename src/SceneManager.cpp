#include <Gambling/SceneManager.h>
#include "Gambling/Scene.h"

SceneManager::SceneManager(sf::RenderWindow* _gameWindow) {
    gameWindow = _gameWindow;
}

void SceneManager::addScene(Scene *scene) {
    this->scenes.push_back(scene);
    scene->setSceneManager(this);
}

void SceneManager::changeScene(const int index) {
    this->activeSceneIndex = index;
    if (activeSceneIndex == -1) return;
    scenes[activeSceneIndex]->start();
}

void SceneManager::update(const float deltaTime) {
    if (activeSceneIndex == -1) return;
    scenes[activeSceneIndex]->update(deltaTime);
}

void SceneManager::render(sf::RenderWindow& window) {
    if (activeSceneIndex == -1) return;
    scenes[activeSceneIndex]->render(window);
}

void SceneManager::eventHandler(sf::Event &event) {
    if (activeSceneIndex == -1) return;
    scenes[activeSceneIndex]->eventHandler(event);
}
