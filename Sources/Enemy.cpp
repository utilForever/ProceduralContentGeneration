#include "PCH.h"
#include "Enemy.h"

// Default constructor.
Enemy::Enemy()
{
	// Set stats.
	m_health = std::rand() % 41 + 80;
	m_attack = std::rand() % 5 + 6;
	m_defense = std::rand() % 5 + 6;
	m_strength = std::rand() % 5 + 6;
	m_dexterity = std::rand() % 5 + 6;
	m_stamina = std::rand() % 5 + 6;

	// Set speed.
	m_speed = rand() % 51 + 150;
}

// Applies the given amount of damage to the enemy.
void Enemy::Damage(int damage)
{
	m_health -= damage;
}

// Checks if the enemy has taken enough damage that they are now dead.
bool Enemy::IsDead()
{
	return (m_health <= 0);
}