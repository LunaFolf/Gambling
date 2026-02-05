#include <iostream>
#include <ostream>
#include <Gambling/Scenes/ui_test.h>

#include "Gambling/Dialogue.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "steam/isteamfriends.h"
#include "steam/isteamremotestorage.h"
#include "steam/isteamscreenshots.h"
#include "steam/isteamuserstats.h"

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

    const char *name = SteamFriends()->GetPersonaName();
    const int friendCount = SteamFriends()->GetFriendCount(k_EFriendFlagImmediate);

    this->addDialogue(new Dialogue(
        "Hello, " + std::string(name) + "... How are you doing today?\n"
        "Looks like you have about... " + std::to_string(friendCount) + " friends!\n"
        "Want me to give you a free achievement? Press enter!\n"
        ":3",
{8, 100},
        Dialogue::Voice::evilgungler,
        "assets/sans.png",
        1,
        [this]() {
            SteamUserStats()->SetAchievement("ACH_TRAVEL_FAR_SINGLE");
            SteamUserStats()->StoreStats();

            this->addDialogue(new Dialogue(
                "Achievement unlocked! Congrats!\n"
                "Wasn't that easy? :3",
                {8, 100},
                Dialogue::Voice::evilgungler,
                "assets/sans.png"
            ));
        }
        ));
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