#include "EBullets.h"



EBullets::EBullets(const sf::Texture& texture, float x, float y)
{

	m_EBulletSprite.setPosition(10, 10);

}


EBullets::~EBullets()
{
}


void EBullets::Update(int dir, int speed, float deltatimes)
{

	m_EBulletSprite.move(0, speed * deltatimes);


}


void EBullets::Draw(sf::RenderWindow& window)
{

	window.draw(m_EBulletSprite);
}

