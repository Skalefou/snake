#include "snake.hpp"

Snake::Snake() {
	resetSnake();
}

void Snake::resetSnake() {
	sf::Vector2f p;
	p.y = 16 * 16;
	m_size = 5;
	m_direction = RIGHT;
	m_snakePos.clear();
	for (unsigned int i = 0; i < m_size; i++) {
		p.x = (float)16 * 16 - (16 * i);
		m_snakePos.push_back(p);
	}
}

void Snake::display(sf::RenderWindow& window) const {
	sf::RectangleShape rect(sf::Vector2f(16.f, 16.f));
	rect.setFillColor(sf::Color(58, 157, 35));
	for (unsigned int i = 0; i < std::size(m_snakePos); i++) {
		rect.setPosition(m_snakePos[i]);
		window.draw(rect);
	}
}

bool Snake::verifSnakeEatTail() const {
	for (unsigned int i = 1; i < std::size(m_snakePos) - 1; i++)
		if (m_snakePos[0].x == m_snakePos[i].x && m_snakePos[0].y == m_snakePos[i].y)
			return true;
	return false;
}

bool Snake::verifDead() const {
	if (((m_snakePos[0].x < 0) ||
		(m_snakePos[0].x > 512) ||
		(m_snakePos[0].y < 0) ||
		(m_snakePos[0].y > 512)) ||
		verifSnakeEatTail())
		return true;
	return false;
}

void Snake::bodyMove() {
	for (unsigned int i = std::size(m_snakePos)-1; i > 0; i--) {
		m_snakePos[i].x = m_snakePos[i - 1].x;
		m_snakePos[i].y = m_snakePos[i - 1].y;
	}
}

void Snake::moveDir(float x, float y, unsigned int direction) {
	bodyMove();
	m_snakePos[0].x += x;
	m_snakePos[0].y += y;
	m_direction = direction;
}

void Snake::moveMain() {
	bool move_put = movePut();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_direction == LEFT)
		moveDir(-16, 0, LEFT);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_direction == RIGHT)
		moveDir(16, 0, RIGHT);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_direction == DOWN)
		moveDir(0, 16, DOWN);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_direction == UP)
		moveDir(0, -16, UP);
	else {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || (!(move_put) && m_direction == RIGHT))
			moveDir(16, 0, RIGHT);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || (!(move_put) && m_direction == LEFT))
			moveDir(-16, 0, LEFT);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || (!(move_put) && m_direction == DOWN))
			moveDir(0, 16, DOWN);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || (!(move_put) && m_direction == UP))
			moveDir(0, -16, UP);
	}

}
