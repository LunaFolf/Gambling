#include <iostream>
#include <ostream>
#include <Gambling/Dialogue.h>

#include "SFML/Window/Event.hpp"

static inline constexpr float charTime = .065f;

Dialogue::Dialogue(
    const std::string& _text,
    const sf::Vector2f _position,
    const Voice voice,
    const std::string& spritePath,
    const float pitch,
    const std::function<void()>& onFinish
    ) {
    text = _text;
    position = _position;
    defaultPitch = pitch;
    chosenVoice = voice;
    onFinishCallback = onFinish;

    setup(spritePath);
}

Dialogue::Dialogue(
    const std::string& _text,
    const float _x,
    const float _y,
    const Voice voice,
    const std::string& spritePath,
    const float pitch,
    const std::function<void()>& onFinish
    ) {
    text = _text;
    position = sf::Vector2f(_x, _y);
    defaultPitch = pitch;
    chosenVoice = voice;
    onFinishCallback = onFinish;

    setup(spritePath);
}

void Dialogue::setup(const std::string& spritePath) {
    box.setPosition(position.x + 82 * 2, position.y + 9 * 2);
    box.setOutlineThickness(4.f);
    box.setOutlineColor(sf::Color::Black);

    soundBuffer.loadFromFile(voicePaths[chosenVoice]);
    sound.setBuffer(soundBuffer);

    bubbleTexture.loadFromFile("assets/sprites/IconBubbleRIVAL.png");
    bubbleSprite.setTexture(bubbleTexture);
    bubbleSprite.setScale(2.f, 2.f);
    bubbleSprite.setPosition(position.x, position.y);

    continuePromptTexture.loadFromFile("assets/sprites/ps/XButton.png");
    continuePromptSprite.setTexture(continuePromptTexture);
    continuePromptSprite.setScale(1.f, 1.f);
    continuePromptSprite.setColor({255, 255, 255, 0});

    continuePromptText.setFont(font);
    continuePromptText.setCharacterSize(32);
    continuePromptText.setFillColor(sf::Color::Transparent);
    continuePromptText.setOutlineColor(sf::Color::Transparent);
    continuePromptText.setOutlineThickness(2.f);
    continuePromptText.setString("Press to continue");

    if (!spritePath.empty()) {
        // 41, 37
        spriteTexture.loadFromFile(spritePath);
        spriteSprite.setTexture(spriteTexture);
        spriteSprite.setScale(2.f, 2.f);
        spriteSprite.setOrigin(spriteTexture.getSize().x / 2.f, spriteTexture.getSize().y / 2.f);
        spriteSprite.setPosition(bubbleSprite.getPosition().x + 41 * 2, bubbleSprite.getPosition().y + 37 * 2);
    }

    font.loadFromFile("assets/fonts/ithaca.ttf");
    font.setSmooth(false);
    dialogueText.setFont(font);
    dialogueText.setPosition(box.getPosition().x + 8, box.getPosition().y);
    dialogueText.setCharacterSize(24);
    dialogueText.setFillColor(sf::Color::Black);

    // Flip text
    std::string temp = text;
    std::reverse(temp.begin(), temp.end());
    text = temp;
}

void Dialogue::render(sf::RenderWindow& window) {
    window.draw(bubbleSprite);
    window.draw(box);
    if (spriteSprite.getTexture()) window.draw(spriteSprite);
    window.draw(dialogueText);

    window.draw(continuePromptSprite);
    window.draw(continuePromptText);
}

void Dialogue::update(const float deltaTime) {
    if (_isDone) return;

    if (_playerHasAdvanced) {
        _isDone = true;
        if (onFinishCallback) onFinishCallback();
        return;
    }


    if (text.empty()) {
        _isFinishedSpeaking = true;

        if (continuePromptSprite.getColor().a < 255) {
            continuePromptSprite.setColor({255, 255, 255, 255});
            continuePromptText.setFillColor(sf::Color::White);
            continuePromptText.setOutlineColor(sf::Color::Black);
        }

        return;
    };

    deltaCount += deltaTime;
    if (deltaCount < (charTime + pausedTime)) return;
    deltaCount = 0;
    pausedTime = 0;

    std::string currentText = dialogueText.getString();
    const char nextChar = text.back();

    switch (nextChar) {
        case ',':
            pausedTime = .25f; break;
        case '.':
        case '!':
        case '?':
            pausedTime = .5f; break;
        case '\n':
            pausedTime = .125f; break;
    }

    dialogueText.setString(currentText + nextChar);
    text.pop_back();

    if (((dialogueText.getGlobalBounds().width + 16) + dialogueText.getPosition().x) >= (720.f - 8)) {
        std::string lastWord = "";
        while (currentText.back() != ' ') {
            std::cout << currentText.back() << std::endl;
            lastWord += currentText.back();
            currentText.pop_back();
        }

        std::reverse(lastWord.begin(), lastWord.end());

        dialogueText.setString(currentText + "\n" + lastWord + nextChar);
    }

    if (!spriteMovedUp) {
        spriteSprite.move(0, -4);
        spriteMovedUp = true;
    } else {
        spriteSprite.move(0, 4);
        spriteMovedUp = false;
    }

    box.setSize({
        dialogueText.getGlobalBounds().width + 16,
        dialogueText.getGlobalBounds().height + 16
    });

    continuePromptSprite.setPosition(box.getPosition().x + 8, box.getPosition().y + box.getSize().y + 8);
    continuePromptText.setPosition(continuePromptSprite.getPosition().x + continuePromptSprite.getGlobalBounds().width + 8, continuePromptSprite.getPosition().y - 8);

    sound.setPitch(defaultPitch + ((std::rand() % 25) / 100.f) - .125f);
    sound.play();
}

void Dialogue::setPosition(const sf::Vector2f _position) {
    position = _position;
}

sf::Vector2f Dialogue::getPosition() {
    return position;
}

std::string Dialogue::getText() {
    return text;
}

void Dialogue::eventHandler(sf::Event &event) {
    if ((_mustFinishDialogueToAdvance && !_isFinishedSpeaking) || _playerHasAdvanced) return;

    if (event.type == sf::Event::JoystickButtonPressed) {
        if (event.joystickButton.button == 0) _playerHasAdvanced = true;
    }
}
