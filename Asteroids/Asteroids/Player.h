#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"
#include "Bullets.h"
#include <stdint.h>


class Player : public Character
{
public:
	Player(const sf::Texture& texture);
	~Player();
	void Update(float deltatime) override;
	void Draw(sf::RenderWindow& window) override;
	float moveX;
	float moveY;

private:
	bool isFriendly;
	sf::Sprite m_Sprite;
	sf::Sprite m_PlayerHealth;


};

