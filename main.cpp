#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(1000, 600), "Dino");

    Texture dinoTexture;
    dinoTexture.loadFromFile("images/PlayerSpriteSheet.png");


    Sprite player_stand;
    Sprite player_left;
    Sprite player_right;
    Sprite open_eye;
    Sprite slope_right;

    player_stand.setTexture(dinoTexture);
    player_stand.setPosition(10, 10);
    player_stand.setTextureRect(IntRect(0, 0, 90, 100));
    player_left.setTextureRect(IntRect(100, 0, 90, 100));


    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(player_stand);
        window.draw(player_left);
        window.draw(player_right);
        window.draw(open_eye);
        //window.draw(slope_left);
        window.draw(slope_right);
        window.display();
    }

    return 0;
}
