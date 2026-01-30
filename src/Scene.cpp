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

void Scene::update(const float deltaTime) {
    for (auto& dialogue : dialogues) {
        if (!dialogue) continue;
        dialogue->update(deltaTime);
        if (!dialogue->isDone()) return;
        delete dialogue;
        dialogue = nullptr;
        dialogues.erase(dialogues.begin());
    }
}

void Scene::render(sf::RenderWindow& window) {
    for (const auto& dialogue : dialogues) {
        if (!dialogue) continue;
        dialogue->render(window);
        if (!dialogue->isDone()) return;
    }
}

void Scene::eventHandler(sf::Event& event) {
    for (const auto& dialogue : dialogues) {
        if (!dialogue) continue;
        dialogue->eventHandler(event);
        if (!dialogue->isDone()) return;
    }
}

void Scene::addDialogue(Dialogue *dialogue) {
    dialogues.push_back(dialogue);
}
