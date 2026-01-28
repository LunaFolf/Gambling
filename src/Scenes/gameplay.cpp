#include <cmath>
#include <Gambling/Scenes/gameplay.h>

float temp = 0;

GameplayScene::GameplayScene() : Scene("Main Gameplay") {
    shells.reserve(8);

    const float padding = 8.f;

    backgroundTexture.loadFromFile("assets/backgrounds/pleb.png");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(2.f, 2.f);

    livesTextures.loadFromFile("assets/sprites/LivesBackground.png");
    livesSprite.setTexture(livesTextures);
    livesSprite.setPosition(720.f - (188.f + padding), padding);
    livesSprite.setScale(2.f, 2.f);

    moneyTexture.loadFromFile("assets/sprites/MoneyBackground.png");
    moneySprite.setTexture(moneyTexture);
    moneySprite.setPosition(padding, 576.f - (122.f + padding));
    moneySprite.setScale(2.f, 2.f);

    font.loadFromFile("assets/fonts/ithaca.ttf");
    moneyText.setFont(font);

    moneyText.setCharacterSize(32*2);
    moneyText.setFillColor(sf::Color::Black);
    moneyText.setOutlineColor(sf::Color::White);
    moneyText.setOutlineThickness(2.f);

}

void GameplayScene::setMoney(const int money) {
    moneyText.setString(std::to_string(money));
    moneyText.setOrigin(moneyText.getLocalBounds().width / 2.f, moneyText.getLocalBounds().height / 2.f);
    moneyText.setPosition(moneySprite.getPosition());
    moneyText.move(92, 61);
}

void GameplayScene::generateShells() {
    shells.clear();

    for (int i = 0; i < 8; i++) {
        bool isShellLive = rand() % 2 == 0;
        shells.push_back(isShellLive);
    }
}

void GameplayScene::start() {
    Scene::start();
}

void GameplayScene::update(const float deltaTime) {
    Scene::update(deltaTime);

    temp += deltaTime * 50;

    setMoney(std::ceil(temp));
}

void GameplayScene::render(sf::RenderWindow& window) {
    Scene::render(window);

    window.draw(backgroundSprite);
    window.draw(livesSprite);
    window.draw(moneySprite);

    window.draw(moneyText);
}