#include <Gambling/Scenes/shoot.h>

ShootScene::ShootScene(GameManager* _gameManager) : Scene("Intro") {
    gameManager = _gameManager;

    liveBuffer.loadFromFile("assets/sfx/gunshot_live.ogg");
    blankBuffer.loadFromFile("assets/sfx/gunshot_blank.ogg");

    liveSound.setBuffer(liveBuffer);
    blankSound.setBuffer(blankBuffer);
}

void ShootScene::start() {
    Scene::start();

    gameManager->pauseAmbientSound();

    if (gameManager->lastFiredBulletWasLive) {
        liveSound.play();
    } else {
        blankSound.play();
    }
}

void ShootScene::update(const float deltaTime) {
    Scene::update(deltaTime);

    if (liveSound.getStatus() == sf::SoundSource::Playing || blankSound.getStatus() == sf::SoundSource::Playing) return;
    this->sceneManager->previousScene();
}

void ShootScene::render(sf::RenderWindow& window) {
    Scene::render(window);
}

void ShootScene::eventHandler(sf::Event &event) {
    Scene::eventHandler(event);
}