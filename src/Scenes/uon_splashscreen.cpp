#include <Gambling/Scenes/uon_splashscreen.h>

#include "../../cmake-build-debug/_deps/sfml-src/include/SFML/Window/Event.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"

UONSplashscreenScene::UONSplashscreenScene () : Scene ("UON Splashscreen") {
    logoTexture.loadFromFile("assets/sprites/UONLogo.png");
    logoSprite.setTexture(logoTexture);
    logoSprite.setOrigin(logoTexture.getSize().x / 2, logoTexture.getSize().y / 2);
    logoSprite.setPosition(720.f / 2.f, 576.f / 2.f);
    logoSprite.setColor({255, 255, 255, 0});
    logoSprite.setScale(2.f, 2.f);
}



void UONSplashscreenScene::start() {
    Scene::start();
}

void UONSplashscreenScene::update (const float deltaTime) {
    Scene::update (deltaTime);

    if (fadingIn && this->clock.getElapsedTime().asSeconds() > fadeTime) {
        fadingIn = false;
        this->clock.restart();
    } else if (!fadingIn && this->clock.getElapsedTime().asSeconds() > fadeTime) {
        this->sceneManager->nextScene();
        delete this;
        return;
    }

    float percent = this->clock.getElapsedTime().asSeconds() / fadeTime;

    if (!fadingIn) percent = 1.f - percent;

    logoSprite.setColor({255, 255, 255, static_cast<sf::Uint8>(255 * percent)});
}

void UONSplashscreenScene::render (sf::RenderWindow& window) {
    Scene::render (window);
    window.draw(logoSprite);
}

void UONSplashscreenScene::eventHandler (sf::Event& event) {
    Scene::eventHandler (event);

    if (event.type == sf::Event::JoystickButtonPressed || event.type == sf::Event::KeyPressed) {
        this->sceneManager->nextScene();
        delete this;
    }
}