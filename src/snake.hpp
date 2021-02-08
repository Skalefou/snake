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
	void display(sf::RenderWindow& window) const;
	bool verifSnakeEatTail() const;
	bool verifDead() const;
	void bodyMove();
	void moveDir(float x, float y, unsigned int direction);
	void moveMain();
	bool appleInSnake(float x, float y) const;
	bool verifEatApple(float x, float y);
	void grow();
private:
	unsigned int m_size, m_direction;
	std::vector<sf::Vector2f> m_snakePos;
};

#endif