#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <string.h>
#include <time.h>
#include <vector>
#include <iostream>
using namespace sf;
using namespace std;

int main()
{
    RenderWindow window(VideoMode(1000, 600), "Dino");
    srand(time(NULL));

    SoundBuffer buffer;
    buffer.loadFromFile("images/dino.mp3");
    Sound sound;
    sound.setBuffer(buffer);
    sound.play();


    //Добавление текстуры птеродактиль
    Texture Pterodactyl;
    Pterodactyl.loadFromFile("images/BirdSpriteSheet.png");
    Sprite pterodact(Pterodactyl);
    Sprite pterodact1(Pterodactyl);
    pterodact.setTextureRect(IntRect(0, 4, 95, 79));
    pterodact.setPosition(900, 170);

    //Добавление текстуры динозаврика
    Texture dinoTexture;
    dinoTexture.loadFromFile("images/PlayerSpriteSheet.png");
    Texture platoTexture;
    platoTexture.loadFromFile("images/GroundImage.png");
    Texture cactusTexture[3];
    cactusTexture[0].loadFromFile("images/Cactus1.png");
    cactusTexture[1].loadFromFile("images/Cactus2.png");
    cactusTexture[2].loadFromFile("images/Cactus3.png");
    //Добавление шрифта
    Font font;
    font.loadFromFile("images/Font8bit.ttf");
    //Добавление текста
    Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(Color::Black);
    text.setString("DINO");
    text.setPosition(window.getSize().x - text.getLocalBounds().width - 10, 10);

    Sprite player_stand;
    Sprite plato1;
    Sprite plato2;

    float gravity = 0.5f;
    float jumpStrength = -10.0f;
    float initialY = 300.0f;
    float yVelocity = 0.0f;

    bool isJumping = false;
    float jumpHeight = 100.0f;

    plato1.setPosition(0, 400);
    plato1.setTexture(platoTexture);

    plato2.setPosition(plato1.getGlobalBounds().width, 400);
    plato2.setTexture(platoTexture);

    player_stand.setTexture(dinoTexture);
    player_stand.setPosition(10, 300);

    int currentSprite = 0;
    float timeSinceLastChange = 0;
    float switchTime = 100;

    Clock gameClock;
    bool isRunning = false;
    bool spacePressed = false;
    vector<Sprite> cactiOnPlatform;

    /*int PterodactylInterval = 600;
    int PterodactylTimer = 0;
    */
    int cactusInterval = 600;
    int cactusTimer = 0;

    while (window.isOpen()) {
        float elapsedTime = gameClock.getElapsedTime().asMicroseconds();
        gameClock.restart();
        elapsedTime = elapsedTime / 1500;

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Space && !isJumping) {
                    isJumping = true;
                    spacePressed = true;
                    yVelocity = jumpStrength;
                }
            }
        }

        if (isJumping) {
            player_stand.move(0, -0.5 * elapsedTime);
            if (player_stand.getPosition().y <= 300 - jumpHeight) {
                isJumping = false;
            }
        }
        else if (player_stand.getPosition().y < 300) {
            player_stand.move(0, 0.5 * elapsedTime);
            if (player_stand.getPosition().y >= 300) {
                player_stand.setPosition(player_stand.getPosition().x, 300);
            }
        }

        player_stand.setTextureRect(IntRect(currentSprite * 98, 0, 98, 110));

        if (spacePressed) {
            timeSinceLastChange += elapsedTime;
            if (timeSinceLastChange >= switchTime) {
                currentSprite++;
                if (currentSprite >= 3) {
                    currentSprite = 0;
                }
                if (currentSprite >= 2) {
                    currentSprite = 0;
                }
                timeSinceLastChange = 0;
            }
            player_stand.setTextureRect(IntRect(currentSprite * 98, 0, 98, 110));
            pterodact.setTextureRect(IntRect(currentSprite * 98, 0, 98, 110));

        }

        if (isRunning) {
            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                player_stand.move(-0.5 * elapsedTime, 0);
            }
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                player_stand.move(0.5 * elapsedTime, 0);
            }
            if (Keyboard::isKeyPressed(Keyboard::Up)) {
                player_stand.move(0, -0.5 * elapsedTime);
            }
            if (Keyboard::isKeyPressed(Keyboard::Down)) {
                player_stand.move(0, 0.5 * elapsedTime);
            }
        }

        plato1.move(-0.2 * elapsedTime, 0);
        plato2.move(-0.2 * elapsedTime, 0);
        pterodact.move(-0.2 * elapsedTime, 0);

        if (plato1.getPosition().x <= -plato1.getGlobalBounds().width) {
            plato1.setPosition(plato2.getPosition().x + plato2.getGlobalBounds().width, 400);
        }

        if (plato2.getPosition().x <= -plato2.getGlobalBounds().width) {
            plato2.setPosition(plato1.getPosition().x + plato1.getGlobalBounds().width, 400);
        }

        cactusTimer += elapsedTime;
        if (cactusTimer >= cactusInterval) {
            int randomTextureIndex = rand() % 3;
            Sprite newCactus;
            newCactus.setTexture(cactusTexture[randomTextureIndex]);
            newCactus.setPosition(window.getSize().x, plato1.getPosition().y - newCactus.getGlobalBounds().height);
            cactiOnPlatform.push_back(newCactus);
            cactusTimer = 0;
        }


        window.clear();
        window.draw(plato1);
        window.draw(plato2);
        window.draw(player_stand);
        window.draw(text);
        window.draw(pterodact);

        for (int i = 0; i < cactiOnPlatform.size(); i++) {
            cactiOnPlatform[i].move(-0.1 * elapsedTime, 0);
            window.draw(cactiOnPlatform[i]);
        }

        window.display();
    }

    return 0;
}

