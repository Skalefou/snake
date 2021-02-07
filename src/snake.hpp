#ifndef SNAKE_HPP
#define SNAKE_HPP
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

enum {UP, RIGHT, DOWN, LEFT};

bool movePut();

class Snake {
public:
	Snake();
	void resetSnake();
	bool verifDead();
	void display(sf::RenderWindow &window);
	void bodyMove();
	void moveMain();
private:
	void moveDir(float x, float y, unsigned int direction);
	bool verifSnakeEatTail();
	unsigned int m_size, m_direction;
	std::vector<sf::Vector2f> m_snakePos;
};

#endif