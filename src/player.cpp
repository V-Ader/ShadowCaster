#include "player.hpp"

Player::Player(sf::Vector2f position)
:position(position), speed(60)
{
}

Player::~Player()
{
}

void Player::setPosition(sf::Vector2f position, bool relative)
{
    if(!relative){
        this->position = position;
    }
    else{
        this->position += position; 
    }
}

sf::Vector2f Player::getPosition()
{
    return this->position;
}

int Player::getSpeed()
{
    return this->speed;
}