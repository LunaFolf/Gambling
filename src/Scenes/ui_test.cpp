#include <iostream>
#include <ostream>
#include <Gambling/Scenes/ui_test.h>

#include "Gambling/Dialogue.h"
#include "Gambling/Dialogue.h"
#include "Gambling/Dialogue.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

UITestScene::UITestScene() : Scene("UI Test") {
    int counter = 0;
    textures.reserve(assets.size());
    for (const std::string& asset : assets) {
        auto& texture = textures.emplace_back();
        if (!texture.loadFromFile(asset)) {
            std::cerr << "Failed to load asset: " << asset << std::endl;
            continue;
        }
        sprites.emplace_back(texture);
        sprites.back().setPosition((56.f * counter) + (8.f * (counter + 1)), 8.f);
        sprites.back().setScale(2.f, 2.f);
        counter++;
    }

    // system("pause");

    // this->addDialogue(new Dialogue(
    //     "WOW! Look at this!\n"
    //     "This Dialogue, starts halfway on the screen, yet is still smart enough to stop before the end of the window!\n"
    //     "Isn't Luna awesome? ALL PRAISE LUNA!\n"
    //     ":3",
    // {8, 100},
    // 1,
    // Dialogue::Voice::gungler,
    // "assets/sprites/SpriteGOODRIVAL.png"
    // ));
    //
    // this->addDialogue(new Dialogue(
    //     "Hey, you.\n"
    //     "You're finally awake.\n"
    //     "You were trying to cross the border, right?\n"
    //     "Walked right into that Imperial ambush, same as us, and that thief over there...",
    //     {8, 576.f * 0.75},
    //     1,
    //     Dialogue::Voice::evilgungler,
    //     "assets/sprites/SpriteEVILRIVAL.png"
    //     ));
}

void UITestScene::start() {
    Scene::start();
}

void UITestScene::update(const float deltaTime) {
    Scene::update(deltaTime);
}

void UITestScene::render(sf::RenderWindow& window) {
    Scene::render(window);

    for (auto& sprite : sprites)
        window.draw(sprite);
}