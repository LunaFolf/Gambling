#pragma once
#include <functional>
#include <string>

#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/System/Vector2.hpp"

class Dialogue {
public:
    enum Voice {
        gungler,
        evilgungler
    };
private:
    sf::RectangleShape box;
    std::string text;
    sf::Vector2f position;
    sf::Font font;
    sf::Text dialogueText;

    sf::Texture bubbleTexture;
    sf::Sprite bubbleSprite;

    sf::Texture spriteTexture;
    sf::Sprite spriteSprite;

    sf::Texture continuePromptTexture;
    sf::Sprite continuePromptSprite;
    sf::Text continuePromptText;

    sf::SoundBuffer soundBuffer;
    sf::Sound sound;

    std::string voicePaths[2] = {
        "assets/sfx/gunglervoiceFIXED.wav",
        "assets/sfx/EVILgunglervoice.wav"
    };

    Voice chosenVoice = gungler;

    bool _mustFinishDialogueToAdvance = true;
    bool _skipDialogue = false;

    float autoSkipDelta = 0.f;
    bool _autoSkip = false;
    bool _isFinishedSpeaking = false;
    bool _playerHasAdvanced = false;
    bool _isDone = false;

    std::function<void()> onFinishCallback = [](){};

    float deltaCount = 0.f;
    float pausedTime = 0.f;

    float defaultPitch = 1.f;

    bool spriteMovedUp = false;

    void setup(const std::string& spritePath);
public:

    Dialogue(
        const std::string& _text,
        sf::Vector2f _position,
        Voice voice = gungler,
        const std::string& spritePath = "",
        const float pitch = 1.f,
        const std::function<void()>& onFinish = [](){},
        bool autoSkip = false
        );
    Dialogue(
        const std::string& _text,
        float _x,
        float _y,
        Voice voice = gungler,
        const std::string& spritePath = "",
        const float pitch = 1.f,
        const std::function<void()>& onFinish = [](){},
        bool autoSkip = false
        );

    std::string getText();
    sf::Vector2f getPosition();

    void render(sf::RenderWindow& window);
    void update(float deltaTime);
    void setPosition(sf::Vector2f _position);
    virtual void eventHandler(sf::Event& event);

    bool isDone () const { return _isDone; };
};
