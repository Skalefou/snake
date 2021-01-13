#include <SFML/Graphics.hpp>

enum {START, IN_GAME, GAME_OVER};
enum {VOID, SNAKE_TAIL, SNAKE_HEAD, APPLE};

void resetMap(unsigned char (*map)[32]) {
    for (int x = 0; x < 32; x++)
        for (int y = 0; y < 32; y++)
            map[x][y] = VOID;
    map[16][16] = SNAKE_HEAD;
}

void inGame(sf::RenderWindow &window, unsigned char(*map)[32]) {
    sf::RectangleShape rect(sf::Vector2f(16.f, 16.f));
    rect.setFillColor(sf::Color(58, 157, 35));


    for (int x = 0; x < 32; x++) {
        for (int y = 0; y < 32; y++) {
            if (map[x][y] == SNAKE_TAIL || map[x][y] == SNAKE_HEAD) {
                rect.setPosition((float)(x * 16), (float)(y * 16));
                window.draw(rect);
            }
        }
    }
}


unsigned int start(sf::RenderWindow &window, unsigned char (*map)[32]) {
    sf::RectangleShape rect(sf::Vector2f(412.f, 187.f));
    sf::Font font;
    sf::Text text[2];

    rect.setFillColor(sf::Color(46, 139, 87));
    rect.setOutlineThickness(1.f);
    rect.setOutlineColor(sf::Color(255, 255, 255));
    rect.setPosition((512 / 2 - 412 / 2), (512/2 - 187/2));

    font.loadFromFile("data/VT323.ttf");
    for (int i = 0; i < 2; i++)
        text[i].setFont(font);
    text[0].setCharacterSize(36);
    text[1].setCharacterSize(30);
    text[0].setString("Snake by Skalefou");
    text[1].setString("Press enter to play\nPress escape to exit");
    text[0].setPosition((512 / 2 - text[0].getLocalBounds().width / 2), 160);
    text[1].setPosition(50, 220);

    window.draw(rect);
    for(int i = 0; i < 2; i++)
        window.draw(text[i]);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        resetMap(map);
        return IN_GAME;
    }
    else
        return START;
}

void setIcon(sf::RenderWindow &window) {
    sf::Image icon;
    if (icon.loadFromFile("data/icon.png"))
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

int main(void) {
    sf::RenderWindow window(sf::VideoMode(512, 512), "Snake", sf::Style::Close);
    unsigned int sleep = 30, gameStep = START;
    unsigned char map[32][32] = { 0 };

    setIcon(window);
    window.setVerticalSyncEnabled(true);

    while (window.isOpen()) {
        sf::sleep(sf::seconds((float)(1 / sleep)));
        window.clear(sf::Color::Black);
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }
        if (gameStep == START)
            gameStep = start(window, map);
        else if (gameStep == IN_GAME)
            inGame(window, map);
        window.display();
    }
    return 0;
}