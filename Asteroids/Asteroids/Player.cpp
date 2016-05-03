#include "Player.h"
#include "Bullets.h"


Player::Player(const sf::Texture& texture) :
	Character(true),
	m_Sprite(texture), moveX(0),
	moveY(0)
{
	m_PlayerHealth.setPosition(100, 100);
	m_Sprite.setPosition(0, 0);

}


Player::~Player()
{
}


void Player::Update(float deltatime)
{
	m_Position = m_Sprite.getPosition();
	m_rrect = m_Sprite.getGlobalBounds();

	int speed = 60 * 8;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		moveY -= speed * deltatime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		moveX += speed * deltatime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		moveY += speed * deltatime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		moveX -= speed * deltatime;
	m_Sprite.setPosition(moveX, moveY);


}
void Player::Draw(sf::RenderWindow& window)
{

	window.draw(m_Sprite);
	window.draw(m_PlayerHealth);
}

