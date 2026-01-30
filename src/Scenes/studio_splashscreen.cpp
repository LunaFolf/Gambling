#include <Gambling/Scenes/studio_splashscreen.h>

#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"

StudioSplashScreenScene::StudioSplashScreenScene () : Scene ("Studio Splashscreen") {
    logoTexture.loadFromFile("assets/sprites/StudioLogo.png");
    logoSprite.setTexture(logoTexture);
    logoSprite.setOrigin(logoTexture.getSize().x / 2, logoTexture.getSize().y / 2);
    logoSprite.setPosition(720.f / 2.f, 576.f / 2.f);
    logoSprite.setColor({255, 255, 255, 0});
}

void StudioSplashScreenScene::start() {
    Scene::start();
}

void StudioSplashScreenScene::update (const float deltaTime) {
    Scene::update (deltaTime);

    if (fadingIn && this->clock.getElapsedTime().asSeconds() > fadeTime) {
        fadingIn = false;
        this->clock.restart();
    } else if (!fadingIn && this->clock.getElapsedTime().asSeconds() > fadeTime) {
        this->sceneManager->changeScene(2);
        delete this;
        return;
    }

    float percent = this->clock.getElapsedTime().asSeconds() / fadeTime;

    if (!fadingIn) percent = 1.f - percent;

    logoSprite.setColor({255, 255, 255, static_cast<sf::Uint8>(255 * percent)});
}

void StudioSplashScreenScene::render (sf::RenderWindow& window) {
    Scene::render (window);
    window.draw(logoSprite);
}