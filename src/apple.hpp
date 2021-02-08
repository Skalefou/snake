#ifndef APPLE_HPP
#define APPLE_HPP
#pragma once

#include "snake.hpp"

class Apple {
public:
	Apple(Snake& snake);
	void generation(Snake &snake);
	void draw(sf::RenderWindow& window);
	void snakeEatApple(Snake &snake, unsigned int &score, sf::RenderWindow &window);
private:
	void texture();
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
};

#endif