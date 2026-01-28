#include <string>
#include <Gambling/Scene.h>

Scene::Scene(const std::string _name) {
    this->name = _name;
}

void Scene::setSceneManager(SceneManager *_sceneManager) {
    this->sceneManager = _sceneManager;
}

void Scene::start() {
    clock.restart();
}

void Scene::update(float deltaTime) {}

void Scene::render(sf::RenderWindow& window) {}

void Scene::eventHandler(sf::Event& event) {}