#include <Gambling/Scenes/intro.h>

#include "SFML/Window/Event.hpp"

IntroScene::IntroScene() : Scene("Intro") {
    this->addDialogue(new Dialogue(
        "I say sir, I've never seen someone fail so terribly as you have!\n"
        "Well, it seems the games are over - time for you to close your tab.\n"
        "How would you like to pay your bill, sir?",
        {8, 8},
        Dialogue::Voice::gungler,
        "assets/sprites/SpriteGOODRIVAL.png",
        1.f,
        [this]() {
            this->addDialogue(new Dialogue(
                "Oh, erm... actually, I forgot my wallet at home...",
                {8, 576.f - (148 + 8)},
                Dialogue::Voice::gungler,
                "assets/sprites/SpritePLAYER.png",
                1.5f,
                [this]() {
                    this->addDialogue(new Dialogue(
                        "Oh? That's alright sir, we have a contingency for this...\n"
                        "Just go meet my colleague down those stairs there... yes, the ones labeled \"basement\"... you'll be fine!",
                        {8, 8},
                        Dialogue::Voice::gungler,
                        "assets/sprites/SpriteGOODRIVAL.png",
                        1.f,
                        [this]() {
                            this->sceneManager->nextScene();
                        }
                    ));
                }
            ));
        }
    ));
}

void IntroScene::start() {
    Scene::start();
}

void IntroScene::update(const float deltaTime) {
    Scene::update(deltaTime);
}

void IntroScene::render(sf::RenderWindow& window) {
    Scene::render(window);
}

void IntroScene::eventHandler(sf::Event &event) {
    Scene::eventHandler(event);
}