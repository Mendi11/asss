#include "GameController.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include "Character.h"
#include "Player.h"
#include "Bullets.h"

GameController::GameController() :
	m_Window(sf::VideoMode(600, 900), "My window"),
	m_Delay(0), m_ESpawn(4), m_Score(0), m_Health(10)
{

	if (!m_font.loadFromFile("fonts/kenvector_future_thin.ttf"))
	{
		//Error
	}
	m_text.setFont(m_font);
	m_text.setColor(sf::Color::White);
	m_text.setPosition(400, 15);
	m_textHP.setFont(m_font);
	m_textHP.setColor(sf::Color::White);
	m_textHP.setPosition(100, 15);
	//m_PlayerHealth.setPosition(100, 50);

	//
	//
	if (!m_PlayerTexture.loadFromFile("Sprites/player.png"))
	{
		//Error
	}
	if (!m_EnemyTexture.loadFromFile("Sprites/enemy.png"))
	{
		//Error
	}
	if (!m_BulletTexture.loadFromFile("Sprites/bullet_player.png"))
	{
		//Error
	}
	if (!m_HealtShip.loadFromFile("Sprites/player_life.png"))
	{
		//Error
	}
	if (!m_EBulletTexture.loadFromFile("Sprites/bullet_enemy.png"))
	{
		//Error
	}

	//sf::FloatRect
	player = new Player(m_PlayerTexture);
	enemie = new Enemie(m_EnemyTexture);
	bullet = new Bullets(m_BulletTexture, 0, 0);
	ebullet = new EBullets(m_EBulletTexture, 0, 0);

	m_Characters.push_back(player);




}


GameController::~GameController()
{
}

void GameController::Run()
{
	while (m_Window.isOpen())
	{
		sf::Event event;
		while (m_Window.pollEvent(event))
		{

			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				m_Window.close();
		}

		Update();
		Draw();
		m_Delay -= dt.asSeconds();
		m_BulletDelay -= dt.asSeconds();
		m_ESpawn -= dt.asSeconds();
		dt = deltaClock.restart();
	}
}


void GameController::Update()
{
	float temp = dt.asSeconds();

	if (m_ESpawn < 0)
	{
		m_ESpawn = 3;
		m_Characters.push_back(new Enemie(m_EnemyTexture));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_Delay < 0.5f)
	{
		m_Delay = 1;
		GetPosition(*player);
		m_Bullets.push_back(new Bullets(m_BulletTexture, playerX + 54, playerY));

	}
	for (int i = 0; i < m_Characters.size(); i++)
	{

		
		m_Characters[i]->Update(temp);
		if (m_Characters[i]->m_Position.y > 1050)
		{
			if (m_Characters[i]->getIsFriendly() == false)
			{
				m_Characters.erase(m_Characters.begin() + i);
			}


		}


		EneimeDir(*m_Characters[i]);
	}
	for (int i = 0; i < m_EBullets.size(); i++)
	{
		m_EBullets[i]->Update(1, 60, temp);
	}
	for (int i = 0; i < m_Bullets.size(); i++)
	{
		float temp = dt.asSeconds();
		m_Bullets[i]->Update(-1, 60 * 11, temp);
		
	/*	if (BulletPosition(*m_Bullets[i]))
		{
			m_Bullets.erase(m_Bullets.begin() + i);
			break;
		}*/

		for (int j = 0; j < m_Characters.size(); j++)
		{
			if (Collision(*m_Bullets[i], *m_Characters[j]) && m_Characters[j]->getIsFriendly() == false)
			{
				std::cout << i << std::endl;

				//m_Bullets.erase(m_Bullets.begin() + i);
				//m_Characters.erase(m_Characters.begin() + j);
				m_Score += 10;
				break;
			}
		}
	}
	if (m_Characters.size() > 1)
	{
		for (int j = 0; j < m_Characters.size(); j++)
		{
			if (PlayerCollision(*m_Characters[0], *m_Characters[j]))
			{
				if (m_Characters[j]->getIsFriendly() == false)
				{
					m_Health--;
					//m_Characters.erase(m_Characters.begin() + j);
				}

				//break;
			}
		}
	}

	
	
			
	if (m_BulletDelay <= 0)
	{ 

		std::cout << "Shoot" << std::endl;
		m_EBullets.push_back(new EBullets(m_EBulletTexture,10,10));
		m_BulletDelay = 3;
	}


	m_text.setString("Score: " + std::to_string(m_Score));
	m_textHP.setString("Health: " + std::to_string(m_Health));




}

void GameController::Draw()
{

	m_Window.clear();

	for (int i = 0; i < m_Characters.size(); i++)
	{
		m_Characters[i]->Draw(m_Window);
	}
	for (int i = 0; i < m_Bullets.size(); i++)
	{
		m_Bullets[i]->Draw(m_Window);
	}
	for (int i = 0; i < m_EBullets.size(); i++)
	{
		m_EBullets[i]->Draw(m_Window);
	}


	//m_Window.draw(m_PlayerHealth);
	m_Window.draw(m_text);
	m_Window.draw(m_textHP);




	m_Window.display();


}

void GameController::GetPosition(const Player &a)
{
	playerX = a.moveX;
	playerY = a.moveY;

}
bool GameController::BulletPosition(const Bullets &a)
{
	if (a.m_BulletSprite.getPosition().y < -10)
	{
		return true;
	}

	return false;


}

void GameController::EneimeDir(Character &a)
{
	if (!a.getIsFriendly())
	{
		if (a.m_Position.x >= 525)
		{
			a.m_ChangeDir = true;

		}
		if (a.m_Position.x <= 0)
		{
			a.m_ChangeDir = false;

		}
	}


}
bool GameController::Collision(const Bullets &a, const Character &b)
{
	if (b.m_rrect.intersects(a.m_rrect))
	{

		return true;
	}
	return false;
}

bool GameController::PlayerCollision(const Character &a, const Character &b)
{

	//std::cout << "Player: " << a.m_rrect.width << " " << a.m_rrect.height << std::endl;
	//std::cout << "Enemie: " << b.m_rrect.width << " " << b.m_rrect.height << std::endl;
	///*std::cout << "Player: "<<  "X :" << a.m_Position.x << " " << "Y :" << a.m_Position.y << std::endl;
	//std::cout << "Enemie: " << "X :" << b.m_Position.x << " " << "Y :" << b.m_Position.y << std::endl;*/
	//

	if (a.m_rrect.intersects(b.m_rrect))
	{
		return true;
	}
	return false;

}