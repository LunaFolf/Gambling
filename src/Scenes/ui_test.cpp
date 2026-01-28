#include <iostream>
#include <ostream>
#include <Gambling/Scenes/ui_test.h>

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