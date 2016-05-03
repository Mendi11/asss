#pragma once

#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Enemie.h"
#include "Bullets.h"

class Character;
class GameController
{
public:
	GameController();
	~GameController();

	void Run();
	void GameController::GetPosition(const Player &a);
	float playerX, playerY;

private:
	bool GameController::Collision(const Bullets &a, const Character &b);
	bool BulletPosition(const Bullets &a);
	void GameController::EneimeDir(Character &a);
	bool PlayerCollision(const Character &a, const Character &b);

	std::vector<sf::Drawable*> m_Draw;
	std::vector<Character*> m_Characters;
	std::vector<Bullets*> m_Bullets;
	std::vector<Bullets*> m_EBullets;

	Bullets* bullet;
	Bullets* ebullet;
	Player* player;
	Enemie* enemie;


	sf::Clock deltaClock;
	sf::Time dt;

	float m_Delay;
	float m_BulletDelay;
	float m_ESpawn;

	sf::Texture m_PlayerTexture;
	sf::Texture m_EnemyTexture;
	sf::Texture m_BulletTexture;
	sf::Texture m_EBulletTexture;
	sf::Texture m_HealtShip;




	void Update();
	void Draw();

	sf::RenderWindow m_Window;

	sf::Text m_text;
	sf::Font m_font;
	sf::Text m_textHP;


	int m_Score;
	int m_Health;



};

