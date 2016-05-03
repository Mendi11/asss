#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Bullets.h"

class Character
{
public:
	Character(bool isFriendly);
	~Character();

	sf::FloatRect m_rrect;
	sf::Vector2f m_Position;
	bool m_ChangeDir = false;

	bool getIsFriendly() const { return this->isFriendly; }

	virtual void Update(float deltatime) = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;

private:
	bool isFriendly;
	int hp;


};

