#include <string>
#include <sstream>
#include "snake.hpp"
#include "apple.hpp"

enum {START, IN_GAME, GAME_OVER};

bool movePut() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		return true;
	return false;
}

void inGame(sf::RenderWindow& window, Snake& snake, unsigned int& gameStep, Apple &apple, unsigned int &score) {
	static sf::Clock clock;
	sf::Time time = clock.getElapsedTime();
	if (time > sf::milliseconds(99)) {
		snake.moveMain();
		if (snake.verifDead())
			gameStep = GAME_OVER;
		apple.snakeEatApple(snake, score, window);
		clock.restart();
	}
	apple.draw(window);
	snake.display(window);
}

void drawText(std::string a, std::string b, sf::RenderWindow& window) {
	sf::Font font;
	sf::Text text[2];

	font.loadFromFile("data/VT323.ttf");
	for (int i = 0; i < 2; i++)
		text[i].setFont(font);
	text[0].setCharacterSize(42);
	text[1].setCharacterSize(36);
	text[0].setString(a);
	text[1].setString(b);
	text[0].setPosition((512 / 2 - text[0].getLocalBounds().width / 2), 160);
	text[1].setPosition(50, 220);
	for (int i = 0; i < 2; i++)
		window.draw(text[i]);
}

void drawRect(sf::Color c, sf::RenderWindow& window) {
	sf::RectangleShape rect(sf::Vector2f(412.f, 187.f));
	rect.setFillColor(c);
	rect.setOutlineThickness(1.f);
	rect.setOutlineColor(sf::Color(255, 255, 255));
	rect.setPosition((512 / 2 - 412 / 2), (512 / 2 - 187 / 2));
	window.draw(rect);
}

unsigned int gameOver(sf::RenderWindow& window, unsigned int& score, Snake& snake, Apple &apple) {
	drawRect(sf::Color(150, 0, 24), window);
	std::ostringstream oss;
	oss << "Score : " << score << "\nPress enter to play\nPress escape to exit";
	std::string t = oss.str();
	drawText("Game Over", t, window);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		snake.resetSnake();
		apple.generation(snake);
		score = 0;
		window.setTitle("Snake! Score : 0");
		return IN_GAME;
	}
	else
		return GAME_OVER;
}

unsigned int start(sf::RenderWindow& window) {
	drawRect(sf::Color(46, 139, 87), window);
	drawText("Snake! by Skalefou", "Pless enter to play\nPress escape to exit", window);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		return IN_GAME;
	else
		return START;
}

void setIcon(sf::RenderWindow& window) {
	sf::Image icon;
	if (icon.loadFromFile("data/icon.png"))
		window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

int main() {
	sf::RenderWindow window(sf::VideoMode(512, 512), "Snake! Score : 0", sf::Style::Close);
	unsigned int gameStep = START, score = 0;
	Snake snake;
	Apple apple(snake);

	setIcon(window);
	window.setVerticalSyncEnabled(true);

	while (window.isOpen()) {
		sf::sleep(sf::microseconds(16'666));
		window.clear(sf::Color::Black);
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}
		if (gameStep == START)
			gameStep = start(window);
		else if (gameStep == IN_GAME)
			inGame(window, snake, gameStep, apple, score);
		else if (gameStep == GAME_OVER)
			gameStep = gameOver(window, score, snake, apple);
		window.display();
	}
	return 0;
}