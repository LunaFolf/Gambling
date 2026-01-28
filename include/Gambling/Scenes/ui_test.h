#pragma once
#include "Gambling/Scene.h"
#include "SFML/Graphics/Sprite.hpp"

class UITestScene : public Scene {
public:
    std::vector<std::string> assets = {
        "assets/sprites/ps/CircleButton.png",
        "assets/sprites/ps/DPADDown.png",
        "assets/sprites/ps/DPADLeft.png",
        "assets/sprites/ps/DPADRight.png",
        "assets/sprites/ps/DPADUp.png",
        "assets/sprites/ps/LeftTrigger2.png",
        "assets/sprites/ps/RightTrigger2.png",
        "assets/sprites/ps/SquareButton.png",
        "assets/sprites/ps/TriangleButton.png",
        "assets/sprites/ps/XButton.png"
    };
    std::vector<sf::Texture> textures{};
    std::vector<sf::Sprite> sprites{};
    UITestScene();

    void start();
    void update(float deltaTime);
    void render(sf::RenderWindow& window);
};
