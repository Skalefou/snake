#include <SFML/Graphics.hpp>

void setIcon(sf::RenderWindow &window) {
    sf::Image icon;
    if (icon.loadFromFile("data/icon.png"))
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

int main(void) {
    sf::RenderWindow window(sf::VideoMode(512, 512), "Snake", sf::Style::Close);
    unsigned int sleep = 30;

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
        window.display();
    }
    return 0;
}

