#include "apple.hpp"
#include <random>
#include <chrono>
#include <string>
#include <sstream>

Apple::Apple(Snake &snake) {
	texture();
	generation(snake);
}

void Apple::generation(Snake &snake) {
	std::default_random_engine re(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_int_distribution <int> d {1, 31};
	do {
		m_position.x = ((float)d(re) * 16);
		m_position.y = ((float)d(re) * 16);
	} while (snake.appleInSnake(m_position.x, m_position.y));
	m_sprite.setPosition(m_position);
}

void Apple::draw(sf::RenderWindow &window) {
	window.draw(m_sprite);
}

void Apple::texture() {
	m_texture.loadFromFile("data/apple.png");
	m_sprite.setTexture(m_texture);
}

void Apple::snakeEatApple(Snake& snake, unsigned int& score, sf::RenderWindow& window) {
	if (snake.verifEatApple(m_position.x, m_position.y)) {
		generation(snake);
		score++;
		snake.grow();
		std::ostringstream oss;
		oss << "Snake! Score : " << score;
		std::string t = oss.str();
		window.setTitle(t);
	}
}