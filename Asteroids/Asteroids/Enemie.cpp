#include "Enemie.h"
#include <iostream>



Enemie::Enemie(const sf::Texture& texture) :
	Character(false), m_Delay(2),
	m_EnemySprite(texture), m_DirSpeed(0)
{

	int randPos = std::rand() % 3;


	if (randPos == 0)
	{
		m_EnemySprite.setPosition(100, 0);

	}
	else if (randPos == 1)
	{
		m_EnemySprite.setPosition(300, 0);

	}
	else
	{
		m_EnemySprite.setPosition(500, 0);

	}


	//	std::cout << randDir << std::endl;

}


Enemie::~Enemie()
{
}

void Enemie::Update(float deltatime)
{
	m_Delay -= deltatime;
	m_rrect = m_EnemySprite.getGlobalBounds();
	m_Position = m_EnemySprite.getPosition();


	//m_rect.setPosition(m_EnemySprite.getPosition());
	m_EnemySprite.move(5 * m_DirSpeed  * deltatime, 3 * 60 * deltatime);



	if (m_ChangeDir == true)
	{
		m_DirSpeed = -60;
	}
	else if (m_ChangeDir == false)
	{
		m_DirSpeed = 60;
	}

}

void Enemie::Draw(sf::RenderWindow& window)
{

	window.draw(m_EnemySprite);
	

}

